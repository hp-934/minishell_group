/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:22:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/20 14:46:15 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_input(int fd, char *delimiter, t_env *env, int j)
{
	char	*str;

	str = readline(">");
	if (!str)
		return (close(fd), unlink(TMP_FILE), ERROR_HEREDOC);
	add_history(str);
	if (ft_strlen(str) == ft_strlen(delimiter)
		&& ft_strncmp(str, delimiter, ft_strlen(str)) == 0)
	{
		free_and_null(&str);
		return (EXIT_FAILURE);
	}
	while (str[j])
	{
		while (str[j] && str[j] != '$')
			ft_putchar_fd(str[j++], fd);
		if (str[j] == '$')
			j = put_variable(str, fd, j, env);
	}
	ft_putchar_fd('\n', fd);
	free_and_null(&str);
	return (EXIT_SUCCESS);
}

char	*get_delimiter(char **array, int i)
{
	char	*delimiter;

	delimiter = NULL;
	while (array[i])
	{
		if (ft_strncmp(array[i], "<<", 2) == 0 && array[i + 1])
		{
			array[i + 1] = remove_quotes_str(array[i + 1]);
			delimiter = array[i + 1];
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

int	handle_heredoc(t_cmd **commands, char **array, int i, t_env *env)
{
	int		fd;
	char	*delimiter;
	int		return_value;

	if (!array[i + 1])
		return (ERROR_SYNTAX);
	delimiter = get_delimiter(array, i);
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (ERROR_FILE);
	while (1)
	{
		return_value = heredoc_input(fd, delimiter, env, 0);
		if (return_value == EXIT_FAILURE)
			break ;
		if (return_value == ERROR_HEREDOC)
			return (return_value);
	}
	close(fd);
	if (heredoc_output(commands) == ERROR_FILE)
		return (ERROR_FILE);
	return (SUCCESS_HEREDOC);
}

char	**remove_redirection_from_args(char **args)
{
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		if (is_redirection(args[i]))
		{
			if (args[i][1] && args[i][0] != args[i][1])
			{
				i++;
				continue ;
			}
			j = 2;
			while (j > 0 && args[i])
			{
				free_and_null(&args[i]);
				args[i++] = ft_strdup("");
				j--;
			}
		}
		else
			i++;
	}
	return (args);
}
