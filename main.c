/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:22:52 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/12 18:00:35 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

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
	t_env	*env;

	(void)argc;
	(void)argv;
	env = duplicate_envp(envp);
	if (!env)
		return (1);
	while (g_signal == 0)
	{
		init_signals();
		str = readline(">");
		if (!str && handle_eof())
			break ;
		add_history(str);
		commands = parser(str, env);
		free_and_null(&str);
		if (!commands)
			continue ;
		find_path(commands, env);
		// print_cmd(commands);
		execute(commands, &env);
		clear_t_cmd(&commands);
	}
	return (clear_history(), free_env(env), get_exit_status());
}
