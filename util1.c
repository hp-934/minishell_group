/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:15:43 by hogu              #+#    #+#             */
/*   Updated: 2025/05/14 15:15:45 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	has_pipe(t_cmd *cmd)
{
	return (cmd && cmd->next);
}

int	has_redirection(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->input_fd != -1 || cmd->output_fd != -1)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	is_pathless_builtin(int is_builtin)
{
	return (is_builtin == BUILTIN_CD
		|| is_builtin == BUILTIN_EXIT
		|| is_builtin == BUILTIN_EXPORT
		|| is_builtin == BUILTIN_UNSET);
}

int	is_must_parent_builtin(t_cmd *cmd)
{
	return (cmd->is_builtin == BUILTIN_CD
		|| cmd->is_builtin == BUILTIN_EXIT
		|| (cmd->is_builtin == BUILTIN_EXPORT && cmd->args[1])
		|| cmd->is_builtin == BUILTIN_UNSET);
}
