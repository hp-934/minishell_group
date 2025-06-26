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


volatile sig_atomic_t	g_signal = 0;

char	*read_input(int interactive)
{
	char	*line = NULL;
	size_t	len = 0;
	ssize_t	nread;

	if (interactive)
		return readline("$ ");
	else
	{
		if (!isatty(fileno(stdout)))
			setvbuf(stdout, NULL, _IONBF, 0);  // 防止缓冲输出卡住

		nread = getline(&line, &len, stdin);
		if (nread <= 0)
		{
			free(line);
			return NULL;
		}
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		return line; // 注意：line 是 malloc 分配的，需要调用者负责 free
	}
}

/* -------------------------------------------------------------------------- */
/* ↓↓↓                                  main                                */
/* -------------------------------------------------------------------------- */
int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_cmd	*commands;
	char	*str;
	int		interactive;

	(void)argc;
	(void)argv;
	interactive = isatty(STDIN_FILENO);        /* 判断是否交互运行        */
	env = duplicate_envp(envp);
	if (!env)
		return (1);
	while (g_signal == 0)
	{
		init_signals();                        /* 仅设置信号 handler      */
		str = read_input(interactive);         /* 获取一行输入            */
		if (!str)
		{
			if (interactive)                   /* 只有交互模式才打印 exit */
				ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (interactive && *str)               /* 交互模式才写 history    */
			add_history(str);
		commands = parser(str, env);
		free_and_null(&str);
		if (!commands)
			continue ;
		find_path(commands, env);
		execute(commands, &env);
		clear_t_cmd(&commands);
	}
	rl_clear_history();                        /* 如果非交互 link 也安全 */
	free_env(env);
	return (get_exit_status());
}
