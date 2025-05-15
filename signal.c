/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   signal.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/08 13:32:56 by hogu           #+#    #+#                */
/*   Updated: 2025/05/08 13:32:57 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
