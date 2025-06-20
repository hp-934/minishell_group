/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execute2.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/20 13:26:09 by hogu           #+#    #+#                */
/*   Updated: 2025/06/20 13:26:10 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(t_cmd *cmd)
{
	if (cmd->is_builtin == NON_BUILTIN
		&& (!cmd->path || !ft_strcmp(cmd->path, PATH_ISDIR)
			|| !ft_strcmp(cmd->path, PATH_NOPERM)
			|| !ft_strcmp(cmd->path, PATH_NOTFOUND)))
	{
		print_cmd_error(cmd);
		exit(get_exit_status());
	}
}

static void	exec_external(t_cmd *cmd, t_env **env_head)
{
	char	**formatted_env;

	check_path(cmd);
	formatted_env = format_char_env(*env_head);
	execve(cmd->path, cmd->args, formatted_env);
	perror("execve failed");
	free_split(formatted_env);
	exit(1);
}

void	child(t_cmd *cmd, int *prev_pipe_out, t_env **env_head, int *pipefd)
{
	child_signals();
	check_redir_error(cmd);
	if (cmd->input_fd > STDERR_FILENO)
		dup2_and_close(cmd->input_fd, STDIN_FILENO, -1);
	else if (*prev_pipe_out > STDERR_FILENO)
		dup2_and_close(*prev_pipe_out, STDIN_FILENO, -1);
	if (cmd->output_fd > STDERR_FILENO)
		dup2_and_close(cmd->output_fd, STDOUT_FILENO, -1);
	else if (cmd->next)
		dup2_and_close(pipefd[1], STDOUT_FILENO, pipefd[0]);
	if (cmd->is_builtin > NON_BUILTIN)
	{
		run_builtin(cmd, env_head);
		exit(get_exit_status());
	}
	else
		exec_external(cmd, env_head);
}
