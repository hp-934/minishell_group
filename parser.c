/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/22 16:14:22 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}

int	put_variable(char *str, int fd, int i)
{
	int		start;
	char	*tmp;
	char	*value;

	start = ++i;
	if (str[start] == '?')
	{
		tmp = ft_itoa(get_exit_status());
		if (!tmp)
			return (0);
		ft_putstr_fd(tmp, fd);
		free(tmp);
		i++;
		return (i);
	}
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$' && str[i] != '"' && str[i] !='\'')
		i++;
	tmp = ft_substr(str, start, i - start);
	value = getenv(tmp);
	free(tmp);
	if (!value)
		return (write_error(ERROR_VAR), 0);
	ft_putstr_fd(value, fd);
	return (i);
}

char	*remove_quotes_expand_variables(char *str)
{
	char	*new;
	char	*tmp;
	int		i;
	int		fd;
	ssize_t	size;
	char	buffer[BUFFER_SIZE];
	char	quote;

	i = 0;
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (ft_strdup(str));
	fd = open("var.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error: Open"), NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				ft_putchar_fd(str[i++], fd);
			if (str[i] == quote)
				i++;
		}
		else if (str[i] == '"')
		{
			quote = str[i];
				i++;
			while (str[i] && str[i] != quote)
			{
				if (str[i] == '$')
				{
					i = put_variable(str, fd, i);
					if (!i)
					{
						close(fd);
						if (unlink("var.txt") != 0)
							perror("Unlink failed");
						return (NULL);
					}
				}
				else
					ft_putchar_fd(str[i++], fd);
			}
			if (str[i] == quote)
				i++;
		}
		else if (str[i] == '$')
		{
			i = put_variable(str, fd, i);
			if (!i)
			{
				close(fd);
				if (unlink("var.txt") != 0)
					perror("Unlink failed");
				return (NULL);
			}
		}
		else
			ft_putchar_fd(str[i++], fd);
	}
	close(fd);
	fd = open("var.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Open");
		return (NULL);
	}
	new = NULL;
	size = read(fd, buffer, BUFFER_SIZE - 1);
	while (size > 0)
	{
		buffer[size] = '\0';
		if (!new)
		{
			new = ft_strdup(buffer);
			if (!new)
				return (NULL);
		}
		else
		{
			tmp  = ft_strjoin(new, buffer);
			if (!tmp)
				return (NULL);
			free(new);
			new = tmp;
		}
		size = read(fd, buffer, BUFFER_SIZE - 1);
	}
	if (size == -1)
	{
		perror("Error: read");
		close(fd);
		if (unlink("var.txt") != 0)
			perror("Unlink failed");
		return (NULL);
	}
	close(fd);
	if (unlink("var.txt") != 0)
		return (perror("Unlink failed"), NULL);
	return (new);
}

char	**tokenize_input(char *str)
{
	char	**args;
	char	*start;
	char	*end;
	int		count;
	int		i;
	char	quote;
	char 	*tmp;

	count = count_args(str);
	if (!count)
		return (NULL);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	start = str;
	i = 0;
	while (i < count)
	{
		while (ft_isspace(*start))
			start++;
		if (!*start)
			break ;
		end = start;
		while (*end && !ft_isspace(*end))
		{
			if (*end == '\'' || *end == '"')
			{
				quote = *end++;
				while (*end && *end != quote)
					end++;
				if (*end == quote)
					end++;
			}
			else
				end++;
		}
		args[i] = ft_substr(start, 0, end - start);
		tmp = remove_quotes_expand_variables(args[i]);
		if (!tmp)
			return (free_arrays((void **)args), NULL);
		free(args[i]);
		args[i] = NULL;
		args[i] = tmp;
		start = ++end;
		i++;
	}
	args[i] = NULL;
	print_char_array(args);
	return (args);
}

char	**split_by_pipes(char *str)
{
	int		i;
	int		count;
	char	**split;
	char	*start;
	char	*end;
	char	quote;

	count = count_commands(str);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	i = 0;
	start = str;
	end = str;
	while (*end)
	{
		if (*end == '\'' || *end == '"')
		{
			quote = *end;
			end++;
			while (*end && *end != quote)
				end++;
			if (*end == quote)
				end++;
		}
		else if (*end == '|')
		{
			split[i++] = ft_substr(start, 0, end - start);
			end++;
			start = end;
		}
		else
			end++;
	}
	split[i++] = ft_substr(start, 0, end - start);
	split[i] = NULL;
	return (split);
}

t_cmd	*parser(char *str)
{
	char	**split;
	t_cmd	*commands;
	t_cmd	*tmp;
	int		i;

	if (check_syntax(str) != EXIT_SUCCESS)
		return (NULL);
	commands = t_cmd_new_empty();
	if (!commands)
		return (NULL);
	tmp = commands;
	split = split_by_pipes(str);
	if (!split)
		return (clear_t_cmd(&commands), NULL);
	i = 0;
	while (split[i])
	{
		tmp->args = tokenize_input(split[i]);
		if (!tmp->args)
			return (free_arrays((void **)split), clear_t_cmd(&commands), NULL);
		if (split[i])
		{
			tmp->next = t_cmd_new_empty();
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
		i++;
	}
	// print_char_array(split);
	free_arrays((void **)split);
	return (commands);
}

int	main(void)
{
	char	*str;
	t_cmd	*commands;

	signal(SIGQUIT, handle_sigquit);
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break ;
		add_history(str);
		commands = parser(str);
		free(str);
		if (commands)
			clear_t_cmd(&commands);
	}
	if (commands)
		clear_t_cmd(&commands);
	rl_clear_history();
	return (0);
}
