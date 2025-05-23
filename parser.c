/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/23 13:40:10 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		start = skip_spaces(start);
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
		free_and_null(&args[i]);
		if (!tmp)
			return (free_arrays((void **)args), NULL);
		args[i] = tmp;
		start = ++end;
		i++;
	}
	args[i] = NULL;
	print_char_array(args);
	return (args);
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
		if (split[i + 1])
		{
			tmp->next = t_cmd_new_empty();
			if (!tmp->next)
				return (free_arrays((void **)split), clear_t_cmd(&commands), NULL);
			tmp = tmp->next;
		}
		i++;
	}
	// print_char_array(split);
	free_arrays((void **)split);
	return (commands);
}
