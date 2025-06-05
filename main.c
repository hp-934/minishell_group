/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:52 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/05 15:02:27 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_signal = 0;

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
		if (commands->args)
			print_char_array(commands->args);
		printf("---PATH---\n");
		if (commands->path)
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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_cmd	*commands;
	t_cmd	*tmp;
	t_env	*env;

	(void)argc;
	(void)argv;
	signal(SIGQUIT, handle_sigquit);
	env = duplicate_envp(envp);
	if (!env)
		return (1);
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break ;
		add_history(str);
		commands = parser(str);
		free_and_null(&str);
		if (!commands)
			continue ;
		tmp = commands;
		while (tmp)
		{
			find_path(tmp, env);
			tmp = tmp->next;
		}
		execute(commands, &env);
		if (commands)
			clear_t_cmd(&commands);
	}
	clear_history();
	return (0);
}
