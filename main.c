/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:52 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/27 16:51:25 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal = 0;

void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}
void	print_cmd(t_cmd *commands)
{
	if (!commands)
		return ;
	while (commands)
	{
		printf("---ARGS---\n");
		print_char_array(commands->args);
		printf("---PATH---\n");
		printf("%s\n", commands->path);
		printf("---IS_BUILDIN---\n");
		printf("%d\n", commands->is_builtin);
		printf("---INPUT_FD---\n");
		printf("%d\n", commands->input_fd);
		printf("---OUTPUT_FD---\n");
		printf("%d\n", commands->output_fd);
		printf("---PID---\n");
		printf("%d\n", commands->pid);
		printf("=======\n");
		commands = commands->next;
	}
}


int	main(void)
{
	char	*str;
	t_cmd	*commands;

	signal(SIGQUIT, handle_sigquit);
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break ;
		add_history(str);
		commands = parser(str);
		free_and_null(&str);
		print_cmd(commands);
		if (commands)
			clear_t_cmd(&commands);
	}
	rl_clear_history();
	return (0);
}
