/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/02 13:24:26 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_by_pipes(char *str, int count)
{
	int		i;
	char	**split;
	char	*end;

	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	i = 0;
	end = str;
	while (*end)
	{
		if (*end == '\'' || *end == '"')
			end = after_quote(end);
		else if (*end == '|')
		{
			split[i++] = ft_substr(str, 0, end - str);
			end++;
			str = end;
		}
		else
			end++;
	}
	split[i++] = ft_substr(str, 0, end - str);
	split[i] = NULL;
	return (split);
}

char	**tokenize_input(char *str)
{
	char	**args;
	char	*end;
	int		count;
	int		i;
	char	*tmp;

	count = count_args(str);
	if (!count)
		return (NULL);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
		end = str;
		while (*end && !ft_isspace(*end))
		{
			if (*end == '\'' || *end == '"')
				end = after_quote(end);
			else
				end++;
		}
		args[i] = ft_substr(str, 0, end - str);
		tmp = remove_quotes_expand_variables(args[i]);
		free_and_null(&args[i]);
		if (!tmp)
			return (free_arrays((void **)args), NULL);
		args[i] = tmp;
		str = ++end;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	check_cmd_args(t_cmd *commands)
{
	char	**tmp;
	int		i;

	if (!commands)
		return (EXIT_FAILURE);
	while (commands)
	{
		tmp = commands->args;
		if (!tmp[0][0])
			return (write_error(ERROR_COMMAND));
		i = 0;
		while (ft_isspace(tmp[0][i]))
			i++;
		if (!tmp[0][i])
			return (write_error(ERROR_COMMAND));
		commands = commands->next;
	}
	return (EXIT_SUCCESS);
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
	split = split_by_pipes(str, count_commands(str));
	if (!split)
		return (clear_t_cmd(&commands), NULL);
	i = 0;
	while (split[i])
	{
		tmp->args = tokenize_input(split[i]);
		if (!tmp->args)
		{
			clear_t_cmd(&commands);
			break ;
		}
		if (split[i + 1])
		{
			tmp->next = t_cmd_new_empty();
			if (!tmp->next)
			{
				clear_t_cmd(&commands);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	free_arrays((void **)split);
	if (check_cmd_args(commands))
		clear_t_cmd(&commands);
	if (commands)
		commands = handle_redirections(&commands);
	return (commands);
}
