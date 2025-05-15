/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_error.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/15 13:47:33 by hogu           #+#    #+#                */
/*   Updated: 2025/05/15 13:47:34 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exit_status.h"

void	print_cmd_error(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (!cmd->path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		set_exit_status(127);
	}
	else if (ft_strcmp(cmd->path, "-1") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory", 2);
		set_exit_status(127);
	}
}
