/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/23 19:33:20 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[j])
	{
		if (toggle_quotes(str[j], &in_single, &in_double) == true)
			j++;
		else
			new[i++] = str[j++];
	}
	new[i] = '\0';
	free_and_null(&str);
	return (new);
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
				return (clear_t_cmd(commands), NULL);
			i++;
		}
		cmd_top = cmd_top->next;
	}
	return (*commands);
}

static bool	append_new_cmd_node(t_cmd **tmp, t_cmd **head)
{
	(*tmp)->next = t_cmd_new_empty();
	if (!(*tmp)->next)
	{
		clear_t_cmd(head);
		return (false);
	}
	*tmp = (*tmp)->next;
	return (true);
}

static int	fill_cmd_list(char **split, t_cmd *head, t_env *env)
{
	t_cmd	*cur;
	int		i;
	int		ok;

	cur = head;
	i = 0;
	ok = 1;
	while (split[i])
	{
		cur->args = tokenize_input(split[i], env);
		if (!cur->args || (split[i + 1]
				&& !append_new_cmd_node(&cur, &head)))
		{
			ok = 0;
			break ;
		}
		i++;
	}
	return (ok);
}

t_cmd	*parser(char *str, t_env *env)
{
	char	**split;
	t_cmd	*commands;

	if (check_syntax(str) != EXIT_SUCCESS)
		return (NULL);
	commands = t_cmd_new_empty();
	if (!commands)
		return (NULL);
	split = split_by_pipes(str, count_commands(str));
	if (!split)
		return (clear_t_cmd(&commands), NULL);
	if (!fill_cmd_list(split, commands, env))
		return (free_arrays((void **)split), clear_t_cmd(&commands), NULL);
	free_arrays((void **)split);
	commands = handle_redirections(&commands, env);
	commands = remove_quotes_cmd(&commands);
	return (commands);
}
