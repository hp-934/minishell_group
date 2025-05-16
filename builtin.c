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

void	run_builtin(t_cmd *cmd)
{
	if (cmd->is_builtin == BUILTIN_ECHO)
		echo_builtin(cmd);
	// else if (cmd->is_builtin == BUILTIN_CD)
	// 	cd_builtin(cmd);
	// else if (cmd->is_builtin == BUILTIN_PWD)
	// 	pwd_builtin(cmd);
	// else if (cmd->is_builtin == BUILTIN_EXPORT)
	// 	export_builtin(cmd);
	// else if (cmd->is_builtin == BUILTIN_UNSET)
	// 	unset_builtin(cmd);
	// else if (cmd->is_builtin == BUILTIN_ENV)
	// 	env_builtin(cmd);
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
}
