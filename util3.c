/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:05:51 by hogu              #+#    #+#             */
/*   Updated: 2025/06/19 18:20:20 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_str_in_array(char **array)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], "") != 0)
			count++;
		i++;
	}
	return (count);
}

static char	**dup_non_empty_args(char **array, t_cmd **head)
{
	size_t	i;
	size_t	j;
	char	**new;

	new = malloc(sizeof(char *) * (count_str_in_array(array) + 1));
	if (!new)
		return (clear_t_cmd(head), NULL);
	i = -1;
	j = 0;
	while (array[++i])
	{
		if (ft_strcmp(array[i], "") != 0)
		{
			new[j] = ft_strdup(array[i]);
			if (!new[j++])
				return (free_arrays((void **)new),
					clear_t_cmd(head), NULL);
		}
	}
	new[j] = NULL;
	return (new);
}

t_cmd	*remove_nul_strs_from_cmd_args(t_cmd **commands)
{
	char	**old;
	char	**new;
	t_cmd	*tmp;

	if (!commands || !*commands)
		return (NULL);
	tmp = *commands;
	while (tmp)
	{
		old = tmp->args;
		if (old)
		{
			new = dup_non_empty_args(old, commands);
			if (!new)
				return (NULL);
			free_arrays((void **)old);
			tmp->args = new;
		}
		tmp = tmp->next;
	}
	return (*commands);
}
