/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/13 18:00:15 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BLANK -1
#define ERROR_SYNTAX 1
volatile int	g_signal = 0;



void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}

int	check_syntax(char *str)
{
	int	count_single;
	int	count_double;

	count_single = 0;
	count_double = 0;
	while (*str)
	{
		if (*str == '\'')
			count_single++;
		else if (*str == '"')
			count_double++;
		if (*str == '\\' && !(count_single %2 == 1 || count_double %2 == 1))
		{
			write(2, "Syntax error: invalid character '\\'\n", 36);
			return (ERROR_SYNTAX);
		}
		if (*str == ';' && !(count_single %2 == 1 || count_double %2 == 1))
		{
			write(2, "Syntax error: invalid character ';'\n", 36);
			return (ERROR_SYNTAX);
		}
		str++;
	}
	if (count_single % 2 == 1 || count_double % 2 == 1)
	{
		write(2, "Syntax error: incorrect quotes\n", 31);
		return (ERROR_SYNTAX);
	}
	return (EXIT_SUCCESS);
}

int	count_args(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (!*str)
			break;
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (*str == '\'')
				str++;
		}
		else if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				str++;
			if (*str == '"')
				str++;
		}
		else
		{
			while (*str && !ft_isspace(*str) && *str != '\'' && *str != '"')
				str++;
		}
		count++;
	}
	printf("count= %d\n", count);
	return (count);
}

char	*expand_variables(char *str)
{
	char	*value;
	char	*start;
	char	*end;
	int		count;

	start = str;
	while (start)
	{
		start = ft_strchr(start, '$');
		if (start)
		{
			start++;
			count = count_args(start);
			if (count == 1)
			{
				value = getenv(start);
				if (!value)
					return (NULL);
				free(str);
				str = ft_strdup(value);
				return (str);
			}
			else /// need to handle variable expansion within quotes ("    $HOME   " "$HOME ")
			{
				start++;
				end = start;
				while (*end &&!ft_isspace(*end))
					end++;
				value = expand_variables(ft_substr(start, 0, end - start));
				if (!value)
					return (NULL);
			}
		start++;
		}
	}
	return (str);
}

char	**tokenize_input(char *str)
{

	char	**args;
	char	*start;
	char	*end;
	int		count;
	int		i;

	count = count_args(str);
	if (!count)
	{
		free(str);
		return (NULL);
	}
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return(NULL);
	start = str;
	i = 0;
	while (i < count)
	{
		while (ft_isspace(*start))
			start++;
		if(!*start)
			break;
		if (*start == '\'')
		{
			start++;
			end = ft_strchr(start, '\'');
			args[i] = ft_substr(start, 0, end - start);
			start = end + 1;
		}
		else if (*start == '"')
		{
			start++;
			end = ft_strchr(start, '"');
			args[i] = ft_substr(start, 0, end - start);
			start = end + 1;
			args[i] = expand_variables(args[i]);
		}
		else
		{
			end = start;
			while (*end && !ft_isspace(*end) && *end != '\'' && *end != '"')
				end++;
			args[i] = ft_substr(start, 0, end - start);
			start = end;
			args[i] = expand_variables(args[i]);
		}
		i++;
	}
	args[i] = NULL;
	print_char_array(args);
	free(str);
	return (args);
}

int	parser(char *str, t_cmd **commands)
{
	if (check_syntax(str ) != EXIT_SUCCESS)
		return (ERROR_SYNTAX);
	add_history(str);
	(*commands)->args = tokenize_input(str);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	char	*str;
	t_cmd	*commands;
	int		error;

	signal(SIGQUIT, handle_sigquit);
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break;
		commands = t_cmd_new_empty();
		if (!commands)
			return (EXIT_FAILURE);
		error = parser(str, &commands);
		if (commands)
			clear_t_cmd(&commands);
	}
	if (commands)
		clear_t_cmd(&commands);
	rl_clear_history();
	return (0);
}