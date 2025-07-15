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

void	dup2_and_close(int fd1, int fd2, int fd3)
{
	dup2(fd1, fd2);
	close(fd1);
	if (fd3 != -1)
		close(fd3);
}
