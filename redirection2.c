/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:22:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/20 13:10:31 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_heredoc(t_cmd **commands, char **array, int i, t_env *env)
{
	int		fd;
	char	*delimiter;
	char	*str;
	int		j;

	if (!array[i + 1])
		return (ERROR_SYNTAX);
	while (array[i])
	{
		if (ft_strncmp(array[i], "<<", 2) == 0 && array[i + 1])
		{
			array[i + 1] = remove_quotes_str(array[i + 1]);
			delimiter = array[i + 1];
		}
		i++;
	}
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (ERROR_FILE);
	while (1)
	{
		str = readline(">");
		if (!str)
		{
			close(fd);
			unlink(TMP_FILE);
			return (ERROR_HEREDOC);
		}
		add_history(str);
		if (ft_strlen(str) == ft_strlen(delimiter)
			&& ft_strncmp(str, delimiter, ft_strlen(str)) == 0)
		{
			free_and_null(&str);
			break ;
		}
		j = 0;
		while (str[j])
		{
			while (str[j] && str[j] != '$')
				ft_putchar_fd(str[j++], fd);
			if (str[j] == '$')
				j = put_variable(str, fd, j, env);
		}
		ft_putchar_fd('\n', fd);
		free_and_null(&str);
	}
	close(fd);
	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	return (SUCCESS_HEREDOC);
}

void	check_redir_error(t_cmd *cmd)
{
	if (cmd->redir_error)
	{
		errno = cmd->errno_saved;
		print_parser_error(cmd->args[0], cmd->redir_error, cmd->bad_token);
		exit(get_exit_status());
	}
}
