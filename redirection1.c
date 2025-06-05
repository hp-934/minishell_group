/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:22:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/02 14:32:34 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (true);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (true);
	if (ft_strncmp(str, "<", 1) == 0)
		return (true);
	if (ft_strncmp(str, ">", 1) == 0)
		return (true);
	return (false);
}

int	handle_heredoc(t_cmd **commands, char **array, int i)
{
	int		fd;
	char	*delimiter;
	char	*str;

	if (!array[i + 1])
		return (ERROR_REDIRECTION);
	delimiter = array[i + 1];
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
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		free_and_null(&str);
	}
	close(fd);
	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	(*commands)->output_fd = STDOUT_FILENO;
	return (EXIT_SUCCESS);
}
