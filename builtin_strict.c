/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_strict.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/22 14:32:08 by hogu           #+#    #+#                */
/*   Updated: 2025/05/22 14:32:09 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"

void	cd_builtin(t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		ft_putendl_fd("cd: usage: cd <path>\n", STDERR_FILENO);
		set_exit_status(1);
		return ;
	}
	else if (cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments\n", STDERR_FILENO);
		set_exit_status(1);
		return ;
	}
	if (chdir(cmd->args[1]) == -1)
	{
		perror("cd");
		set_exit_status(1);
		return ;
	}
	set_exit_status(0);
}
