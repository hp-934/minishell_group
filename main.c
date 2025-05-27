/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:52 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/27 15:16:36 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}
void	print_cmd_args(t_cmd *commands)
{
	if (!commands)
		return ;
	while (commands)
	{
		print_char_array(commands->args);
		commands = commands->next;
	}
}
int	check_cmd_args(t_cmd *commands)
{
	char	**tmp;

	if (!commands)
		return (write_error(ERROR_COMMAND));
	while (commands)
	{
		tmp = commands->args;
		if (!tmp[0][0])
			return (write_error(ERROR_COMMAND));
		commands = commands->next;
	}
	return (EXIT_SUCCESS);
}

int	main(void)
{
	char	*str;
	t_cmd	*commands;
	int		error;

	signal(SIGQUIT, handle_sigquit);
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break ;
		add_history(str);
		commands = parser(str);
		free_and_null(&str);
		error = check_cmd_args(commands);
		if (error)
			clear_t_cmd(&commands);
		print_cmd_args(commands);
		if (commands)
			clear_t_cmd(&commands);
	}
	rl_clear_history();
	return (0);
}
