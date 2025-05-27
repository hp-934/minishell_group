/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/27 17:55:40 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_stdin_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (EXIT_FAILURE);
	file = args[i + 1];
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	(*commands)->input_fd = fd;
	return (EXIT_SUCCESS);
}

int	redirect_stdout_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (EXIT_FAILURE);
	file = args[i + 1];
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (EXIT_FAILURE);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

int	append_stdout_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (EXIT_FAILURE);
	file = args[i + 1];
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (EXIT_FAILURE);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

// bool	handle_heredoc(t_cmd **commands, char **args, int i)
// {

// }

bool	is_redirection(char *str)
{
	if (ft_strncmp(str, "<", 2) == 0)
		return (true);
	if (ft_strncmp(str, ">", 2) == 0)
		return (true);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (true);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (true);
	return (false);
}

char	**remove_redirection_from_args(char **args)
{
	int		i;
	int		j;

	i = 0;
	while(args[i] && args[i + 1])
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

t_cmd	*handle_redirections(t_cmd **commands)
{
	char	**array;
	int 	i;
	bool	error;
	t_cmd	*commands_top;

	if (!commands || !*commands)
		return (NULL);
	error = false;
	commands_top = *commands;
	while (*commands)
	{
		array = (*commands)->args;
		i = 0;
		while (array[i] && !error)
		{
			if (ft_strncmp(array[i], "<", 2) == 0)
				error = redirect_stdin_file(commands, array, i);
			else if (ft_strncmp(array[i], ">", 2) == 0)
				error = redirect_stdout_file(commands, array, i);
			else if (ft_strncmp(array[i], ">>", 1) == 0)
				error = redirect_stdout_file(commands, array, i);
			// else if (ft_strncmp(array[i], "<<", 1) == 0)
			// 	error = redirect_stdout_file(commands, array, i);
			if (error)
			{
				write_error(ERROR_REDIRECTION);
				return (clear_t_cmd(commands), NULL);
			}
			i++;
		}
		array = remove_redirection_from_args(array);
		(*commands) = (*commands)->next;
	}
	return (commands_top);
}