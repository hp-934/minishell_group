/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:47:33 by hogu              #+#    #+#             */
/*   Updated: 2025/06/10 14:13:52 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_error(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	if (!cmd->path)
	{
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		set_exit_status(127);
	}
	else if (ft_strcmp(cmd->path, PATH_NOTFOUND) == 0)
	{
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		set_exit_status(127);
	}
	else if (ft_strcmp(cmd->path, PATH_ISDIR) == 0)
	{
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		set_exit_status(126);
	}
	else if (ft_strcmp(cmd->path, PATH_NOPERM) == 0)
	{
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		set_exit_status(126);
	}
}

void	print_builtin_error(int builtin, char *str)
{
	if (builtin == BUILTIN_EXIT)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_signal = 1;
		set_exit_status(2);
	}
	else if (builtin == BUILTIN_CD)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else if (builtin == BUILTIN_EXPORT)
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		set_exit_status(1);
	}
}

void	sig_write_next_line(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
