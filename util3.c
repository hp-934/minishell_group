/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:05:51 by hogu              #+#    #+#             */
/*   Updated: 2025/06/12 17:32:08 by yaepark          ###   ########.fr       */
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

t_cmd	*remove_nul_strs_from_cmd_args(t_cmd **commands)
{
	int		i;
	int		j;
	char	**new_array;
	char	**array;
	t_cmd	*tmp;

	if (!commands || !*commands)
		return (NULL);
	tmp = *commands;
	while (tmp)
	{
		array = tmp->args;
		if (!array)
		{
			tmp = tmp->next;
			continue ;
		}
		i = 0;
		j = 0;
		new_array = malloc(sizeof(char *) * (count_str_in_array(array) + 1));
		if (!new_array)
			return (clear_t_cmd(commands), NULL);
		while (array[i])
		{
			if (ft_strcmp(array[i], "") != 0)
			{
				new_array[j] = ft_strdup(array[i]);
				if (!new_array[j])
				{
					free_arrays((void **)new_array);
					clear_t_cmd(commands);
					return (NULL);
				}
				j++;
			}
			i++;
		}
		new_array[j] = NULL;
		tmp->args = new_array;
		free_arrays((void **)array);
		tmp = tmp->next;
	}
	return (*commands);
}
