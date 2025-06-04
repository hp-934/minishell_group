/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/15 14:12:34 by hogu           #+#    #+#                */
/*   Updated: 2025/05/15 14:12:36 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"

int	check_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo") && args[1] && !ft_strcmp(args[1], "-n"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(args[0], "cd"))
		return (BUILTIN_CD);
	if (!ft_strcmp(args[0], "pwd") && args[1] == NULL)
		return (BUILTIN_PWD);
	if (!ft_strcmp(args[0], "export"))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(args[0], "unset"))
		return (BUILTIN_UNSET);
	if (!ft_strcmp(args[0], "env") && args[1] == NULL)
		return (BUILTIN_ENV);
	if (!ft_strcmp(args[0], "exit"))
		return (BUILTIN_EXIT);
	return (0);
}

void	run_builtin(t_cmd *cmd, t_env **env_head)
{
	if (cmd->is_builtin == BUILTIN_ECHO)
		echo_builtin(cmd);
	else if (cmd->is_builtin == BUILTIN_CD)
		cd_builtin(cmd, *env_head);
	else if (cmd->is_builtin == BUILTIN_PWD)
		pwd_builtin();
	else if (cmd->is_builtin == BUILTIN_EXPORT)
		export_builtin(cmd, *env_head);
	else if (cmd->is_builtin == BUILTIN_UNSET)
		unset_builtin(cmd, env_head);
	else if (cmd->is_builtin == BUILTIN_ENV)
		env_builtin(*env_head);
	else if (cmd->is_builtin == BUILTIN_EXIT)
		exit_builtin(cmd);
}

void	echo_builtin(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && ft_strcmp(cmd->args[i + 1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	set_exit_status(0);
}

void	pwd_builtin(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		set_exit_status(1);
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	set_exit_status(0);
}

void	env_builtin(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	set_exit_status(0);
}
