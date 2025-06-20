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

int	valid_identifier(char *str, int *exit_value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		print_builtin_error(BUILTIN_EXPORT, str);
		if (*str == '-')
			*exit_value = 2;
		else
			*exit_value = 1;
		return (0);
	}
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			print_builtin_error(BUILTIN_EXPORT, str);
			*exit_value = 1;
			return (0);
		}
	}
	return (1);
}

int	is_n_variant(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

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
