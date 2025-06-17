/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   write_error.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yaepark <yaepark@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/15 16:48:57 by yaepark		   #+#	#+#			 */
/*   Updated: 2025/06/05 15:39:52 by yaepark		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int write_error(char *cmd_name, int error_type, char *token)
{
	int exit_code;

	// 1) 根据错误类型决定最终的退出码
	if (error_type == ERROR_SYNTAX || error_type == ERROR_REDIRECTION)
		exit_code = 2;
	else if (error_type == ERROR_FILE || error_type == ERROR_HEREDOC)
		exit_code = 1;
	else
		exit_code = 1;
	// 2) 先把全局退出码设好
	set_exit_status(exit_code);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_type == ERROR_SYNTAX)
	{
		// Bash: syntax error near unexpected token `|`
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token ? token : "", STDERR_FILENO);
		ft_putendl_fd("`", STDERR_FILENO);
	}
	else if (error_type == ERROR_REDIRECTION)
	{
		// Bash: parse error near `<'
		ft_putstr_fd("parse error near `", STDERR_FILENO);
		ft_putstr_fd(token ? token : "", STDERR_FILENO);
		ft_putendl_fd("`", STDERR_FILENO);
	}
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
	{
		ft_putstr_fd("warning: here-document delimited by end-of-file\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}
