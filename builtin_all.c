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

int	check_builtin(char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(args[0], "cd"))
		return (BUILTIN_CD);
	if (!ft_strcmp(args[0], "pwd") && (!args[1] || args[1][0] != '-'))
		return (BUILTIN_PWD);
	if (!ft_strcmp(args[0], "export"))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(args[0], "unset"))
		return (BUILTIN_UNSET);
	if (!ft_strcmp(args[0], "env") && args[1] == NULL)
		return (BUILTIN_ENV);
	if (!ft_strcmp(args[0], "exit"))
		return (BUILTIN_EXIT);
	return (NON_BUILTIN);
}

void	run_builtin(t_cmd *cmd, t_env **env_head)
{
	if (cmd->is_builtin == BUILTIN_ECHO)
		echo_builtin(cmd);
	else if (cmd->is_builtin == BUILTIN_CD)
		cd_builtin(cmd, *env_head);
	else if (cmd->is_builtin == BUILTIN_PWD)
		pwd_builtin(*env_head);
	else if (cmd->is_builtin == BUILTIN_EXPORT)
		export_builtin(cmd, *env_head);
	else if (cmd->is_builtin == BUILTIN_UNSET)
		unset_builtin(cmd, env_head);
	else if (cmd->is_builtin == BUILTIN_ENV)
		env_builtin(*env_head);
	else if (cmd->is_builtin == BUILTIN_EXIT)
		exit_builtin(cmd);
}

int	is_pathless_builtin(int is_builtin)
{
	return (is_builtin == BUILTIN_CD
		|| is_builtin == BUILTIN_EXIT
		|| is_builtin == BUILTIN_EXPORT
		|| is_builtin == BUILTIN_UNSET);
}

int	is_must_parent_builtin(t_cmd *cmd)
{
	return (cmd->is_builtin == BUILTIN_CD
		|| cmd->is_builtin == BUILTIN_EXIT
		|| (cmd->is_builtin == BUILTIN_EXPORT && cmd->args[1])
		|| cmd->is_builtin == BUILTIN_UNSET);
}
