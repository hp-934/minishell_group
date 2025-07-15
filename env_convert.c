/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:07:38 by hogu              #+#    #+#             */
/*   Updated: 2025/06/04 14:07:39 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_to_struct(t_env *env, char *entry)
{
	int	equal_len;
	int	str_len;

	if (!entry)
		return (1);
	str_len = ft_strlen(entry);
	equal_len = 0;
	while (entry[equal_len] && entry[equal_len] != '=')
		equal_len++;
	env->name = ft_substr(entry, 0, equal_len);
	if (entry[equal_len] == '=')
		env->value = ft_substr(entry, equal_len + 1, str_len - equal_len - 1);
	else
		env->value = NULL;
	return (0);
}

char	*struct_to_char(t_env *env)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(env->name, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	if (!result)
		return (free(tmp), NULL);
	return (result);
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
	if (!result)
		return (NULL);
	if (char_to_struct(result, envp[0]))
		return (free_env(result), NULL);
	i = 1;
	current = result;
	while (envp[i])
	{
		tmp = init_env();
		if (char_to_struct(tmp, envp[i]))
			return (free_env(result), free_env(tmp), NULL);
		current->next = tmp;
		current = current->next;
		i++;
	}
	return (result);
}

int	count_env(t_env *env)
{
	int		count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**format_char_env(t_env *env)
{
	int		count;
	int		i;
	char	**result;

	count = count_env(env);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = struct_to_char(env);
		if (!result[i])
			return (free_split(result), NULL);
		i++;
		env = env->next;
	}
	result[count] = NULL;
	return (result);
}
