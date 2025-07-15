/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_error.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/11 11:58:05 by hogu           #+#    #+#                */
/*   Updated: 2025/07/11 11:58:06 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_error(char *str, int msg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (msg == EXIT_NON_NUM)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_signal = 1;
		set_exit_status(2);
	}
	else if (msg == EXIT_TOO_MANY)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
}

void	print_cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (errno == EACCES)
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	else
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

void	print_export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (*str == '-')
		ft_putendl_fd("': invalid option", STDERR_FILENO);
	else
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

void	print_unset_error(char *str)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	set_exit_status(2);
}
