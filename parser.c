/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/19 23:09:51 by yaepark          ###   ########.fr       */
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

char	**tokenize_input(char *str, t_env *env)
{
	char	**args;
	char	*end;
	int		count;
	int		i;
	char	*tmp;
	char	c;

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
		if (is_redirection(end))
		{
			c = *end;
			while (*end == c)
				end++;
			args[i++] = ft_substr(str, 0, end - str);
			str = end;
			continue ;
		}
		while (*end && !ft_isspace(*end))
		{
			if (*end == '\'' || *end == '"')
				end = after_quote(end);
			else if (is_redirection(end))
				break ;
			else
				end++;
		}
		args[i] = ft_substr(str, 0, end - str);
		tmp = expand_variables(args[i], env);
		free_and_null(&args[i]);
		if (!tmp)
			return (free_arrays((void **)args), NULL);
		args[i++] = tmp;
		str = end;
	}
	args[i] = NULL;
	return (args);
}

char	*remove_quotes_str(char *str)
{
	int		i;
	int		j;
	bool	in_single;
	bool	in_double;
	char	*new;

	in_single = false;
	in_double = false;
	i = 0;
	j = 0;
	new = malloc(ft_strlen(str) + 1);
	if (!new)
		return (free_and_null(&str), NULL);
	while(str[j])
	{
		if (toggle_quotes(str[j], &in_single, &in_double) == true)
			j++;
		else
			new[i++] = str[j++];
	}
	new[i] = '\0';
	free_and_null(&str);
	return(new);
}

t_cmd	*remove_quotes_cmd(t_cmd **commands)
{
	char	**array;
	t_cmd	*cmd_top;
	int		i;

	cmd_top = *commands;
	while (cmd_top)
	{
		array = cmd_top->args;
		i = 0;
		while (array[i])
		{
			array[i] = remove_quotes_str(array[i]);
			if (!array[i])
				return(clear_t_cmd(commands), NULL);
			i++;
		}
		cmd_top = cmd_top->next;
	}
	return(*commands);
}

t_cmd	*parser(char *str, t_env *env)
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
		tmp->args = tokenize_input(split[i], env);
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
	commands = handle_redirections(&commands, env);
	commands = remove_quotes_cmd(&commands);
	return (commands);
}
