/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/21 12:27:10 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}

char	*remove_quotes_expand_variables(char *str)
{
	char	*value;
	char	*tmp;
	int		start;
	int		i;
	int		fd;
	ssize_t	size;
	char	buffer[BUFFER_SIZE];
	char	quote;

	i = 0;
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (str);
	fd = open("var.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error: Open"), free(str), NULL);
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
					start = ++i;
					if (str[start] == '?')
					{
						//tmp = ft_itoa(get_exit_status());
						//if (!tmp)
						//	return (free(str), close(fd), NULL);
						//ft_putstr_fd(tmp, fd);
						//free(tmp);
						i++;
						continue ;
					}
					while (str[i] && !ft_isspace(str[i]) && str[i] != '$' && str[i] != quote)
						i++;
					tmp = ft_substr(str, start, i - start);
					value = getenv(tmp);
					free(tmp);
					if (!value)
						return (write_error(ERROR_VAR), free(str), NULL);
					ft_putstr_fd(value, fd);
					if (str[i] == quote)
					{
						i++;
						break;
					}
				}
				ft_putchar_fd(str[i++], fd);
			}
		}
		else if (str[i] == '$')
		{
			start = ++i;
			if (str[start] == '?')
			{
				//tmp = ft_itoa(get_exit_status());
				//if (!tmp)
				//	return (free(str), close(fd), NULL);
				//ft_putstr_fd(tmp, fd);
				//free(tmp);
				i++;
				continue ;
			}
			while (str[i] && !ft_isspace(str[i]) && str[i] != '$' && str[i] != '"' && str[i] !='\'')
				i++;
			tmp = ft_substr(str, start, i - start);
			value = getenv(tmp);
			free(tmp);
			if (!value)
				return (write_error(ERROR_VAR), free(str), NULL);
			ft_putstr_fd(value, fd);
		}
		else
			ft_putchar_fd(str[i++], fd);
	}
	free(str);
	str = NULL;
	close(fd);
	fd = open("var.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Open");
		return (NULL);
	}
	size = read(fd, buffer, BUFFER_SIZE - 1);
	while (size > 0)
	{
		buffer[size] = '\0';
		if (!str)
			str = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(str, buffer);
			free(str);
			str = tmp;
		}
		size = read(fd, buffer, BUFFER_SIZE - 1);
	}
	if (size == -1)
	{
		perror("Error: read");
		close(fd);
		if (unlink("var.txt") != 0)
			perror("Unlink failed");
		if (str)
			free(str);
		return (NULL);
	}
	close(fd);
	if (unlink("var.txt") != 0)
		return (perror("Unlink failed"), NULL);
	return (str);
}

char	**tokenize_input(char *str)
{
	char	**args;
	char	*start;
	char	*end;
	int		count;
	int		i;
	char	quote;

	count = count_args(str);
	if (!count)
	{
		free(str);
		return (NULL);
	}
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
				quote = *end;
				end++;
				end = ft_strchr(end, quote);
			}
			end++;
		}
		args[i] = ft_substr(start, 0, end - start);
		start = end++;
		args[i] = remove_quotes_expand_variables(args[i]);
		if (!args[i])
			return (free_arrays((void **)args), free(str), NULL);
		i++;
		//if (*start == '\'')
		//{
		//	start++;
		//	end = ft_strchr(start, '\'');
		//	args[i] = ft_substr(start, 0, end - start);
		//	start = end + 1;
		//}
		//else if (*start == '"')
		//{
		//	start++;
		//	end = ft_strchr(start, '"');
		//	args[i] = ft_substr(start, 0, end - start);
		//	start = end + 1;
		//	args[i] = expand_variables(args[i]);
		//	if (!args[i])
		//		return (free_arrays((void **)args), free(str), NULL);
		//}
		//else
		//{
		//	end = start;
		//	while (*end && !ft_isspace(*end) && *end != '\'' && *end != '"')
		//		end++;
		//	args[i] = ft_substr(start, 0, end - start);
		//	start = end;
		//	args[i] = expand_variables(args[i]);
		//	if (!args[i])
		//	{
		//		free_arrays((void **)args);
		//		free(str);
		//		return (NULL);
		//	}
		//}
	}
	args[i] = NULL;
	print_char_array(args);
	free(str);
	return (args);
}

void	parser(char *str, t_cmd **commands)
{
	if (check_syntax(str) != EXIT_SUCCESS)
		return ;
	(*commands)->args = tokenize_input(str);
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
		commands = t_cmd_new_empty();
		if (!commands)
			return (EXIT_FAILURE);
		add_history(str);
		parser(str, &commands);
		if (commands)
			clear_t_cmd(&commands);
	}
	if (commands)
		clear_t_cmd(&commands);
	rl_clear_history();
	return (0);
}
