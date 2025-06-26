/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:11:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/26 11:53:05 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redir_error(t_cmd *cmd)
{
	if (cmd->redir_error)
	{
		errno = cmd->errno_saved;
		print_parser_error(cmd->args[0], cmd->redir_error, cmd->bad_token);
		exit(get_exit_status());
	}
}

bool	is_redirection(char *str)
{
	bool	result;

	result = false;
	if (ft_strncmp(str, ">>", 2) == 0)
		result = true;
	if (ft_strncmp(str, "<<", 2) == 0)
		result = true;
	if (ft_strncmp(str, "<", 1) == 0)
		result = true;
	if (ft_strncmp(str, ">", 1) == 0)
		result = true;
	return (result);
}

t_cmd	*set_redirection_errors(t_cmd **cmd_top, int i, int result)
{
	char	**array;

	array = (*cmd_top)->args;
	(*cmd_top)->redir_error = result;
	if (result == ERROR_REDIRECTION)
		(*cmd_top)->bad_token = ft_strdup(array[i]);
	else if (result == ERROR_FILE)
	{
		(*cmd_top)->bad_token = ft_strdup(array[i + 1]);
		(*cmd_top)->errno_saved = errno;
	}
	else
		(*cmd_top)->bad_token = ft_strdup(array[i]);
	return (*cmd_top);
}

int	handle_heredoc(t_cmd **commands, char **array, t_env *env)
{
	int		fd;
	char	*delimiter;
	int		return_value;

	delimiter = get_delimiter(array);
	if (!delimiter)
		return (SUCCESS_HEREDOC);
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (free_and_null(&delimiter), ERROR_FILE);
	while (1)
	{
		return_value = heredoc_input(fd, delimiter, env);
		if (return_value == EOF_HEREDOC)
			break ;
		if (return_value == ERROR_HEREDOC)
			return (free_and_null(&delimiter), return_value);
	}
	close(fd);
	free_and_null(&delimiter);
	if (heredoc_output(commands) == ERROR_FILE)
		return (ERROR_FILE);
	if (return_value == EOF_HEREDOC)
		return (handle_heredoc(commands, array, env));
	return (SUCCESS_HEREDOC);
}

t_cmd	*handle_redirections(t_cmd **commands, t_env *env)
{
	char	**array;
	int		i;
	int		result;
	t_cmd	*cmd_top;

	cmd_top = *commands;
	while (cmd_top)
	{
		array = cmd_top->args;
		i = 0;
		while (array[i] && cmd_top->redir_error == 0)
		{
			result = redirect(&cmd_top, array, i, env);
			if (result)
			{
				if (result == SUCCESS_HEREDOC)
					continue ;
				cmd_top = set_redirection_errors(&cmd_top, i, result);
			}
			i++;
		}
		array = remove_redirection_from_args(array);
		cmd_top = cmd_top->next;
	}
	return (remove_nul_strs_from_cmd_args(commands));
}
