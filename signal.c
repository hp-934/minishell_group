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

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	refresh_prompt(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	(void)sig;
	set_exit_status(128 + SIGINT);
	refresh_prompt();
}

int	handle_eof(void)
{
	printf("exit\n");
	return (1);
}
