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

void	child(t_cmd *cmd, int *prev_pipe_out, t_env **env_head, int *pipefd)
{
	char	**formatted_env;

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
	if (cmd->is_builtin > NON_BUILTIN)
	{
		run_builtin(cmd, env_head);
		exit(get_exit_status());
	}
	else
	{
		formatted_env = format_char_env(*env_head);
		execve(cmd->path, cmd->args, formatted_env);
		perror("execve failed");
		exit(1);
	}
}

int	run_single_cmd(t_cmd *cmd, int *prev_pipe_out, t_env **env_head)
{
	int		pipefd[2];
	pid_t	pid;

	if (cmd->is_builtin == NON_BUILTIN
		&& (!cmd->path || !ft_strcmp(cmd->path, "-1")))
		return (print_cmd_error(cmd), -1);
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
}

void	wait_and_exit(t_cmd *cmd)
{
	int	status;
	int	last_exit;
	int	had_child;

	had_child = 0;
	last_exit = get_exit_status();
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			had_child = 1;
			waitpid(cmd->pid, &status, 0);
			if (WIFEXITED(status))
				last_exit = WEXITSTATUS(status);
			else
				last_exit = 1;
		}
		cmd = cmd->next;
	}
	if (had_child)
		set_exit_status(last_exit);
}

void	execute(t_cmd *cmd, t_env **env_head)
{
	int		prev_pipe_out;

	prev_pipe_out = -1;
	run_all_cmd(cmd, &prev_pipe_out, env_head);
	wait_and_exit(cmd);
}
