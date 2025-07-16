/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:44:17 by hogu              #+#    #+#             */
/*   Updated: 2025/06/23 15:44:18 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_get_path(t_cmd *cmd, t_env *env, int *print_path)
{
	char	*path;

	if (print_path)
		*print_path = 0;
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		set_exit_status(1);
		return (NULL);
	}
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~")
		|| !ft_strcmp(cmd->args[1], "--"))
		path = ft_getenv("HOME", env);
	else if (!cmd->args[1][0])
		return (set_exit_status(0), NULL);
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		if (print_path)
			*print_path = 1;
		path = ft_getenv("OLDPWD", env);
	}
	else
		path = cmd->args[1];
	return (path);
}

static char	*cd_get_oldpwd(t_env *env)
{
	char	*val;

	val = ft_getenv("PWD", env);
	if (val)
		return (ft_strdup(val));
	return (getcwd(NULL, 0));
}

static void	cd_report_phisical_fail(void)
{
	ft_putendl_fd("cd: error retrieving current directory: "
		"getcwd: cannot access parent directories: No such file"
		" or directory", STDERR_FILENO);
}

static char	*cd_cal_newpwd(char *path, char *old_pwd)
{
	char	*new_pwd;
	char	*slash;
	char	*tmp;

	cd_report_phisical_fail();
	if (path[0] == '/')
		return (ft_strdup(path));
	else if (ft_strcmp(path, "..") == 0)
	{
		slash = ft_strrchr(old_pwd, '/');
		if (slash == old_pwd || !slash)
			return (ft_strdup("/"));
		*slash = '\0';
		new_pwd = ft_strdup(old_pwd);
		*slash = '/';
		return (new_pwd);
	}
	else if (ft_strcmp(path, ".") == 0)
		return (ft_strdup(old_pwd));
	else
	{
		tmp = ft_strjoin(old_pwd, "/");
		new_pwd = ft_strjoin(tmp, path);
		return (free(tmp), new_pwd);
	}
}

void	cd_builtin(t_cmd *cmd, t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*path;
	int		print_path;

	print_path = 0;
	path = cd_get_path(cmd, env, &print_path);
	if (!path)
		return ;
	old_pwd = cd_get_oldpwd(env);
	if (!old_pwd || chdir(path) == -1)
	{
		if (!old_pwd)
			cd_report_phisical_fail();
		else
			print_cd_error(path);
		return (free(old_pwd), (void)set_exit_status(1));
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		new_pwd = cd_cal_newpwd(path, old_pwd);
	if (print_path)
		ft_putendl_fd(new_pwd, STDOUT_FILENO);
	update_cd_env(env, old_pwd, new_pwd);
	return (free(old_pwd), free(new_pwd), (void)set_exit_status(0));
}
