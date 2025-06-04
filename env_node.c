/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:20 by hogu              #+#    #+#             */
/*   Updated: 2025/06/04 14:09:21 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"

t_env	*search_node(char *target, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(target, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	append_node(char *name, char *value, t_env *env)
{
	t_env	*new;

	new = init_env();
	new->name = name;
	new->value = value;
	new->next = NULL;
	while (env->next)
		env = env->next;
	env->next = new;
}

void	replace_node(char *name, char *value, t_env *env)
{
	free(env->value);
	env->value = value;
	free(name);
}

void	remove_node(t_env **head_ptr, char *name)
{
	t_env	dummy;
	t_env	*prev;
	t_env	*cur;

	dummy.next = *head_ptr;
	prev = &dummy;
	cur = *head_ptr;
	while (cur)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			prev->next = cur->next;
			free(cur->name);
			free(cur->value);
			free(cur);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	*head_ptr = dummy.next;
}
