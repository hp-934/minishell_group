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
#include "exit_status.h"

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

int	get_info(t_env *env, char *entry)
{
	int	equal_len;
	int	str_len;

	if (!entry)
		return (1);
	str_len = ft_strlen(entry);
	equal_len = 0;
	while (entry[equal_len] != '=')
		equal_len++;
	if (entry[equal_len] != '=')
		return (1);
	env->name = ft_substr(entry, 0, equal_len);
	env->value = ft_substr(entry, equal_len + 1, str_len - equal_len - 1);
	return (0);
}

void	ft_free(t_env *env)
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

t_env	*duplicate_envp(char **envp)
{
	int		i;
	t_env	*result;
	t_env	*current;
	t_env	*tmp;

	if (!envp || !envp[0])
		return (NULL);
	result = init_env();
	if (get_info(result, envp[0]))
		return (free(result), NULL);
	i = 1;
	current = result;
	while (envp[i])
	{
		tmp = init_env();
		if (get_info(tmp, envp[i]))
			return (ft_free(result), free(tmp), NULL);
		current->next = tmp;
		current = current->next;
		i++;
	}
	return (result);
}
