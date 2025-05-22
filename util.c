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
	while (s1[i + 1] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	has_pipe(t_cmd *cmd)
{
	return (cmd && cmd->next);
}

int	is_strict_builtin(int is_builtin)
{
	return (is_builtin == BUILTIN_CD
		|| is_builtin == BUILTIN_EXIT
		|| is_builtin == BUILTIN_EXPORT
		|| is_builtin == BUILTIN_UNSET);
}

void	dup2_and_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}