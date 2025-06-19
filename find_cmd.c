/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:39:40 by hogu              #+#    #+#             */
/*   Updated: 2025/06/19 22:13:54 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**get_folders(t_env *env)
{
	char	**folders;

	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	folders = ft_split(env->value, ':');
	if (!folders)
		return (NULL);
	return (folders);
}

char	*search_path(char *cmd, t_env *env)
{
	char	**folders;
	char	*temp;
	char	*path;
	int		i;

	folders = get_folders(env);
	if (!folders)
		return (NULL);
	i = 0;
	while (folders[i])
	{
		temp = ft_strjoin(folders[i], "/");
		if (!temp)
			return (free_split(folders), NULL);
		path = ft_strjoin(temp, cmd);
		if (!path)
			return (free_split(folders), NULL);
		free(temp);
		if (access(path, X_OK) == 0)
			return (free_split(folders), path);
		free(path);
		i++;
	}
	return (free_split(folders), NULL);
}

void	slashed_path(char *str, t_cmd *cmd)
{
	struct stat	st;

	if (stat(str, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			cmd->path = ft_strdup(PATH_ISDIR);
		else if (S_ISREG(st.st_mode) && access(str, X_OK) == 0)
			cmd->path = ft_strdup(str);
		else
			cmd->path = ft_strdup(PATH_NOPERM);
	}
	else
		cmd->path = ft_strdup(PATH_NOTFOUND);
}

void	find_path(t_cmd *cmd, t_env *env)
{
	char		*command;

	while (cmd)
	{
		if (!cmd->args || !cmd->args[0])
			return ;
		command = cmd->args[0];
		cmd->is_builtin = check_builtin(cmd->args);
		if (ft_strchr(command, '/'))
			slashed_path(command, cmd);
		else if (!is_pathless_builtin(cmd->is_builtin))
			cmd->path = search_path(command, env);
		cmd = cmd->next;
	}
}
