/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:58:01 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/20 14:08:45 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_stdin_file(t_cmd **commands, char **args, int i)
{
	int		fd;

	if (!args[i + 1])
		return (ERROR_SYNTAX);
	args[i + 1] = remove_quotes_str(args[i + 1]);
	fd = open(args[i + 1], O_RDONLY);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	return (EXIT_SUCCESS);
}

int	redirect_stdout_file(t_cmd **commands, char **args, int i)
{
	int		fd;

	if (!args[i + 1])
		return (ERROR_SYNTAX);
	args[i + 1] = remove_quotes_str(args[i + 1]);
	fd = open(args[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

int	append_stdout_file(t_cmd **commands, char **args, int i)
{
	int		fd;

	if (!args[i + 1])
		return (ERROR_SYNTAX);
	args[i + 1] = remove_quotes_str(args[i + 1]);
	fd = open(args[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

int	redirect(t_cmd **commands, char **array, int i, t_env *env)
{
	int	result;

	result = EXIT_SUCCESS;
	if (ft_strncmp(array[i], ">>", 2) == 0)
		result = append_stdout_file(commands, array, i);
	else if (ft_strncmp(array[i], "<<", 2) == 0)
		result = handle_heredoc(commands, array, i, env);
	else if (ft_strncmp(array[i], ">", 1) == 0)
		result = redirect_stdout_file(commands, array, i);
	else if (ft_strncmp(array[i], "<", 1) == 0)
		result = redirect_stdin_file(commands, array, i);
	return (result);
}
