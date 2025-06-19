/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   signal2.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/19 12:05:53 by hogu           #+#    #+#                */
/*   Updated: 2025/06/19 12:05:56 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_write_next_line(int sig)
{
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}