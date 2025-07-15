/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   execute.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/09 13:17:54 by hogu           #+#    #+#                */
/*   Updated: 2025/05/09 13:17:59 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_single_cmd(t_cmd *cmd, int *prev_pipe_out, t_env **env_head)
{
	int		pipefd[2];
	pid_t	pid;

	if (cmd->next && pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork error"), -1);
	if (!pid)
		child(cmd, prev_pipe_out, env_head, pipefd);
	if (*prev_pipe_out != -1)
		close(*prev_pipe_out);
	if (cmd->next)
	{
		*prev_pipe_out = pipefd[0];
		close(pipefd[1]);
	}
	else
		*prev_pipe_out = -1;
	return (pid);
}

void	run_all_cmd(t_cmd *cmd, int *prev_pipe_out, t_env **env_head)
{
	if (!has_pipe(cmd) && is_must_parent_builtin(cmd))
		run_builtin(cmd, env_head);
	else
	{
		while (cmd)
		{
			cmd->pid = run_single_cmd(cmd, prev_pipe_out, env_head);
			cmd = cmd->next;
		}
	}
	if (*prev_pipe_out > STDERR_FILENO)
		close(*prev_pipe_out);
	*prev_pipe_out = -1;
}

void	wait_and_exit(t_cmd *cmd)
{
	int	status;
	int	last_exit;
	int	sig;

	last_exit = get_exit_status();
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				sig_write_next_line(sig);
				last_exit = 128 + sig;
			}
		}
		else
			last_exit = get_exit_status();
		cmd = cmd->next;
	}
	set_exit_status(last_exit);
}

void	execute(t_cmd *cmd, t_env **env_head)
{
	int		prev_pipe_out;

	signal(SIGINT, SIG_IGN);
	prev_pipe_out = -1;
	run_all_cmd(cmd, &prev_pipe_out, env_head);
	wait_and_exit(cmd);
}
