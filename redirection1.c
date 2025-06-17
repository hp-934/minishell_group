/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:22:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/17 17:32:35 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(char *str)
{
	bool	result;

	result = false;
	if (ft_strncmp(str, ">>", 2) == 0)
		result = true;
	if (ft_strncmp(str, "<<", 2) == 0)
		result = true;
	if (ft_strncmp(str, "<", 1) == 0)
		result = true;
	if (ft_strncmp(str, ">", 1) == 0)
		result = true;
	return (result);
}

int	handle_heredoc(t_cmd **commands, char **array, int i, t_env *env)
{
	int		fd;
	char	*delimiter;
	char	*str;
	int		j;

	if (!array[i + 1])
		return (ERROR_SYNTAX);
	while (array[i])
	{
		if (ft_strncmp(array[i], "<<", 2) == 0 && array[i + 1])
			delimiter = array[i + 1];
		i++;
	}
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (ERROR_FILE);
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			close(fd);
			unlink(TMP_FILE);
			return (ERROR_HEREDOC);
		}
		add_history(str);
		if (ft_strlen(str) == ft_strlen(delimiter)
			&& ft_strncmp(str, delimiter, ft_strlen(str)) == 0)
		{
			free_and_null(&str);
			break ;
		}
		j = 0;
		while (str[j])
		{
			while (str[j] && str[j] != '$')
				ft_putchar_fd(str[j++], fd);
			if (str[j] == '$')
				j = put_variable(str, fd, j, env);
		}
		// ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		free_and_null(&str);
	}
	close(fd);
	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	return (SUCCESS_HEREDOC);
}
