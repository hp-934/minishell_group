/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/02 14:39:17 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_stdin_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!commands || !*commands)
		return (ERROR_COMMAND);
	if (!args || args[i + 1])
		return (ERROR_REDIRECTION);
	file = args[i + 1];
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), ERROR_FILE);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	return (EXIT_SUCCESS);
}

int	redirect_stdout_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (ERROR_REDIRECTION);
	file = args[i + 1];
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

int	append_stdout_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (ERROR_REDIRECTION);
	file = args[i + 1];
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

char	**remove_redirection_from_args(char **args)
{
	int		i;
	int		j;

	i = 0;
	while (args[i] && args[i + 1])
	{
		if (is_redirection(args[i]))
		{
			j = 0;
			while (j < 2)
			{
				free_and_null(&args[i]);
				args[i++] = ft_strdup("");
				j++;
			}
		}
		else
			i++;
	}
	return (args);
}

int redirect (t_cmd **commands, char **array, int i)
{
	int	error;

	error = EXIT_SUCCESS;
	if (ft_strncmp(array[i], ">>", 2) == 0)
		error = append_stdout_file(commands, array, i);
	else if (ft_strncmp(array[i], "<<", 2) == 0)
		error = handle_heredoc(commands, array, i);
	else if (ft_strncmp(array[i], ">", 1) == 0)
		error = redirect_stdout_file(commands, array, i);
	else if (ft_strncmp(array[i], "<", 1) == 0)
		error = redirect_stdin_file(commands, array, i);
	return (error);
}

t_cmd	*handle_redirections(t_cmd **commands)
{
	char	**array;
	int		i;
	int		error;
	t_cmd	*commands_top;

	if (!commands || !*commands)
		return (NULL);
	error = EXIT_SUCCESS;
	commands_top = *commands;
	while (*commands)
	{
		array = (*commands)->args;
		i = 0;
		while (array[i] && !error)
		{
			error = redirect(commands, array, i);
			if (error)
			{
				write_error(error);
				clear_t_cmd(&commands_top);
				return (commands_top);
			}
			i++;
		}
		array = remove_redirection_from_args(array);
		(*commands) = (*commands)->next;
	}
	return (commands_top);
}
