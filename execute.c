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
#include "exit_status.h"

void	child(t_cmd *cmd, int *prev_pipe_out, char **envp, int *pipefd)
{
	if (cmd->input_fd != -1)
		dup2_and_close(cmd->input_fd, STDIN_FILENO);
	if (*prev_pipe_out != -1)
		dup2_and_close(*prev_pipe_out, STDIN_FILENO);
	if (cmd->output_fd != -1)
		dup2_and_close(cmd->output_fd, STDOUT_FILENO);
	else if (cmd->next)
	{
		dup2_and_close(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
	}
	if (cmd->is_builtin)
	{
		run_builtin(cmd, envp);
		exit(get_exit_status());
	}
	else
	{
		execve(cmd->path, cmd->args, envp);
		perror("execve failed");
		exit(1);
	}
}

int	run_single_cmd(t_cmd *cmd, int *prev_pipe_out, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (is_strict_builtin(cmd->is_builtin))
		return (-1);
	if (!cmd->path || !ft_strcmp(cmd->path, "-1"))
		return (print_cmd_error(cmd), -1);
	if (cmd->next && pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork error"), -1);
	if (!pid)
		child(cmd, prev_pipe_out, envp, pipefd);
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

void	run_all_cmd(t_cmd *cmd, int *prev_pipe_out, char **envp)
{
	if (!has_pipe(cmd) && is_strict_builtin(cmd->is_builtin))
		run_builtin(cmd, envp);
	else
	{
		while (cmd)
		{
			cmd->pid = run_single_cmd(cmd, prev_pipe_out, envp);
			cmd = cmd->next;
		}
	}
}

void	wait_and_exit(t_cmd *cmd)
{
	int	status;
	int	last_exit;

	last_exit = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else
				last_exit = 1;
		}
		cmd = cmd->next;
	}
	set_exit_status(last_exit);
}

void	execute(t_cmd *cmd, char **envp)
{
	int		prev_pipe_out;

	prev_pipe_out = -1;
	run_all_cmd(cmd, &prev_pipe_out, envp);
	wait_and_exit(cmd);
}
