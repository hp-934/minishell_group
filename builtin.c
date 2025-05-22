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

void	run_builtin(t_cmd *cmd, char **envp)
{
	if (cmd->is_builtin == BUILTIN_ECHO)
		echo_builtin(cmd);
	else if (cmd->is_builtin == BUILTIN_CD)
		cd_builtin(cmd);
	else if (cmd->is_builtin == BUILTIN_PWD)
		pwd_builtin();
	// else if (cmd->is_builtin == BUILTIN_EXPORT)
	// 	export_builtin(cmd);
	// else if (cmd->is_builtin == BUILTIN_UNSET)
	// 	unset_builtin(cmd);
	else if (cmd->is_builtin == BUILTIN_ENV)
		env_builtin(envp);
	// else if (cmd->is_builtin == BUILTIN_EXIT)
	// 	exit_builtin(cmd);
}

void	echo_builtin(t_cmd *cmd)
{
	int	i;

	i = 2;
	while (cmd->args[i + 1])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
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

void	env_builtin(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	set_exit_status(0);
}