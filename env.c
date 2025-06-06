/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:40:18 by hogu              #+#    #+#             */
/*   Updated: 2025/05/23 12:40:19 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		env = env->next;
	}
}

t_env	*locate_next_node(char *prev_name, t_env *head)
{
	t_env	*current;

	current = NULL;
	while (head)
	{
		if (!prev_name || prev_name[0] == '\0'
			|| ft_strcmp(head->name, prev_name) > 0)
		{
			if (!current || ft_strcmp(current->name, head->name) > 0)
				current = head;
		}
		head = head->next;
	}
	return (current);
}

void	print_env_az(t_env *env)
{
	t_env	*node;
	char	*prev_name;

	prev_name = "";
	node = locate_next_node(prev_name, env);
	while (node)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(node->name, STDOUT_FILENO);
		if (node->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(node->value, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putstr_fd("\n", STDOUT_FILENO);
		prev_name = node->name;
		node = locate_next_node(prev_name, env);
	}
	set_exit_status(0);
}
