/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:22:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/23 20:48:08 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_input(int fd, char *delimiter, t_env *env, int j)
{
	char	*str;
	char	*dequoted_delimiter;

	str = readline(">");
	if (!str)
		return (close(fd), unlink(TMP_FILE), ERROR_HEREDOC);
	add_history(str);
	dequoted_delimiter = remove_quotes_str(delimiter);
	if (ft_strcmp(str, dequoted_delimiter) == 0)
	{
		free_and_null(&str);
		return (EOF_HEREDOC);
	}
	while (str[j])
	{
		while (str[j] && str[j] != '$')
			ft_putchar_fd(str[j++], fd);
		if (str[j] == '$')
		{
			if (*delimiter == '"' || *delimiter == '\'')
				ft_putchar_fd(str[j++], fd);
			else
				j = put_variable(str, fd, j, env);
		}
	}
	ft_putchar_fd('\n', fd);
	free_and_null(&str);
	free_and_null(&dequoted_delimiter);
	return (EXIT_SUCCESS);
}

void	remove_token_and_delimiter(char ***args)
{
	int		i;
	int		j;

	i = 0;
	while ((*args)[i])
	{
		if (ft_strncmp((*args)[i], "<<", 2) == 0)
		{
			j = 2;
			while (j > 0 && (*args)[i])
			{
				free_and_null(&(*args)[i]);
				(*args)[i++] = ft_strdup("");
				j--;
			}
			break ;
		}
		else
			i++;
	}
}

char	*get_delimiter(char **array)
{
	char	*delimiter;
	int		i;

	delimiter = NULL;
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], "<<", 2) == 0 && array[i + 1])
		{
			delimiter = ft_strdup(array[i + 1]);
			remove_token_and_delimiter(&array);
			break ;
		}
		i++;
	}
	return (delimiter);
}

int	heredoc_output(t_cmd **commands)
{
	int		fd;

	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_cmd **commands, char **array, t_env *env)
{
	int		fd;
	char	*delimiter;
	int		return_value;

	delimiter = get_delimiter(array);
	if (!delimiter)
		return (SUCCESS_HEREDOC);
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (free_and_null(&delimiter), ERROR_FILE);
	while (1)
	{
		return_value = heredoc_input(fd, delimiter, env, 0);
		if (return_value == EOF_HEREDOC)
			break ;
		if (return_value == ERROR_HEREDOC)
			return (free_and_null(&delimiter), return_value);
	}
	close(fd);
	free_and_null(&delimiter);
	if (heredoc_output(commands) == ERROR_FILE)
		return (ERROR_FILE);
	if (return_value == EOF_HEREDOC)
		return (handle_heredoc(commands, array, env));
	return (SUCCESS_HEREDOC);
}
