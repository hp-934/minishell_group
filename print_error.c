/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:47:33 by hogu              #+#    #+#             */
/*   Updated: 2025/06/19 14:41:27 by yaepark          ###   ########.fr       */
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
		if (*str == '-')
			ft_putendl_fd("': invalid option", STDERR_FILENO);
		else
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
}

static void	print_parser_error_type(int error_type, char *token)
{
	if (!token)
		token = "";
	if (error_type == ERROR_SYNTAX)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else if (error_type == ERROR_REDIRECTION)
	{
		ft_putstr_fd("parse error near `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
}

int	print_parser_error(char *cmd_name, int error_type, char *token)
{
	int	exit_code;

	if (error_type == ERROR_SYNTAX || error_type == ERROR_REDIRECTION)
		exit_code = 2;
	else
		exit_code = 1;
	set_exit_status(exit_code);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_type == ERROR_SYNTAX || error_type == ERROR_REDIRECTION)
		print_parser_error_type(error_type, token);
	else if (error_type == ERROR_FILE)
	{
		if (token && *token)
			ft_putstr_fd(token, STDERR_FILENO);
		else if (cmd_name && *cmd_name)
			ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else if (error_type == ERROR_HEREDOC)
		ft_putstr_fd("warning: here-document delimited by end-of-file\n",
			STDERR_FILENO);
	else
		ft_putstr_fd("error\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
