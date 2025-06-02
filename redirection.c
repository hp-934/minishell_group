/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:39:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/02 13:54:05 by yaepark          ###   ########.fr       */
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
		return (perror("open") ,ERROR_FILE);
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
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_cmd **commands, char **args, int i)
{
	int		fd;
	char 	*delimiter;
	char	*str;
	size_t	len;
	int		saved_stdin;

	if (!args[i + 1])
		return (ERROR_REDIRECTION);
	delimiter = args[i + 1];
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (ERROR_FILE);
	saved_stdin = dup(STDIN_FILENO);
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			close(fd);
			unlink(TMP_FILE);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
			return(ERROR_HEREDOC);
		}
		add_history(str);
		len = strlen(str);
		if (len < strlen(delimiter))
			len = strlen(delimiter);
		if (ft_strncmp(str, delimiter, len) == 0)
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
	(*commands)->input_fd = fd;
	(*commands)->output_fd = STDOUT_FILENO;
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	return (EXIT_SUCCESS);
}

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
			if (ft_strncmp(array[i], ">>", 2) == 0)
				error = append_stdout_file(commands, array, i);
			else if (ft_strncmp(array[i], "<<", 2) == 0)
				error = handle_heredoc(commands, array, i);
			else if (ft_strncmp(array[i], ">", 1) == 0)
				error = redirect_stdout_file(commands, array, i);
			else if (ft_strncmp(array[i], "<", 1) == 0)
				error = redirect_stdin_file(commands, array, i);
			if (error)
			{
				write_error(error);
				clear_t_cmd(&commands_top);
				return (commands_top) ;
			}
			i++;
		}
		array = remove_redirection_from_args(array);
		(*commands) = (*commands)->next;
	}
	return (commands_top);
}
