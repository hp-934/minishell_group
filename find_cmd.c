/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   find_cmd.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 15:39:40 by hogu           #+#    #+#                */
/*   Updated: 2025/05/13 15:39:49 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"

int	check_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo") && args[1] && !ft_strcmp(args[1], "-n"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(args[0], "cd") && args[1] && args[2] == NULL)
		return (BUILTIN_CD);
	if (!ft_strcmp(args[0], "pwd") && args[1] == NULL)
		return (BUILTIN_PWD);
	if (!ft_strcmp(args[0], "export") && args[1] == NULL)
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(args[0], "unset") && args[1] == NULL)
		return (BUILTIN_UNSET);
	if (!ft_strcmp(args[0], "env") && args[1] == NULL)
		return (BUILTIN_ENV);
	if (!ft_strcmp(args[0], "exit") && args[1] == NULL)
		return (BUILTIN_EXIT);
	return (0);
}

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

char	**get_folders(char *envp[])
{
	int		i;
	char	**folders;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	folders = ft_split(envp[i] + 5, ':');
	if (!folders)
		return (NULL);
	return (folders);
}

char	*search_path(char *cmd, char **envp)
{
	char	**folders;
	char	*temp;
	char	*path;
	int		i;

	folders = get_folders(envp);
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

void	find_path(t_cmd *cmd, char **envp)
{
	char	*command;

	if (!cmd->args || !cmd->args[0])
		return ;
	command = cmd->args[0];
	cmd->is_builtin = check_builtin(cmd->args);
	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			cmd->path = ft_strdup(command);
		else
			cmd->path = "-1";
	}
	else
			cmd->path = search_path(command, envp);
}
