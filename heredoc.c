/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:22:32 by hogu              #+#    #+#             */
/*   Updated: 2025/06/27 16:10:10 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint(int sig)
{
	(void)sig;
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = 2;
}

static int	heredoc_read_loop(int *pipefd, char *delim, t_env *env)
{
	int	ret;

	while (!g_signal)
	{
		ret = heredoc_input(pipefd, delim, env);
		if (ret == EOF_HEREDOC)
			return (EOF_HEREDOC);
		if (ret == ERROR_HEREDOC)
			return (ERROR_HEREDOC);
	}
	return (ERROR_HEREDOC);
}

void	parse_heredoc_input(char *str, char *delimiter, int *pipefd, t_env *env)
{
	int	j;

	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] != '$')
			ft_putchar_fd(str[j++], pipefd[1]);
		if (str[j] == '$')
		{
			if (*delimiter == '"' || *delimiter == '\'')
				ft_putchar_fd(str[j++], pipefd[1]);
			else
				j = put_variable(str, pipefd[1], j, env);
		}
	}
}

int	heredoc_input(int *pipefd, char *delimiter, t_env *env)
{
	char	*str;
	char	*dequoted_delimiter;

	str = readline(">");
	if (!str)
		return (ERROR_HEREDOC);
	add_history(str);
	dequoted_delimiter = remove_quotes_str(delimiter);
	if (ft_strcmp(str, dequoted_delimiter) == 0)
	{
		free_and_null(&str);
		free_and_null(&dequoted_delimiter);
		return (EOF_HEREDOC);
	}
	parse_heredoc_input(str, delimiter, pipefd, env);
	ft_putchar_fd('\n', pipefd[1]);
	free_and_null(&str);
	free_and_null(&dequoted_delimiter);
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_cmd **commands, char **array, t_env *env)
{
	char	*delimiter;
	int		return_value;
	int		pipefd[2];

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	delimiter = get_delimiter(array);
	if (!delimiter)
		return (init_signals(), SUCCESS_HEREDOC);
	pipe(pipefd);
	if (pipe(pipefd) == 1)
		return (perror("pipe"), -1);
	return_value = heredoc_read_loop(pipefd, delimiter, env);
	close(pipefd[1]);
	if (return_value == ERROR_HEREDOC || g_signal == 2)
		return (free_and_null(&delimiter), init_signals(), close(pipefd[0]),
			g_signal = 0, ERROR_HEREDOC);
	free_and_null(&delimiter);
	init_signals();
	if (heredoc_output(commands, pipefd) == ERROR_FILE)
		return (ERROR_FILE);
	if (return_value == EOF_HEREDOC)
		return (handle_heredoc(commands, array, env));
	return (SUCCESS_HEREDOC);
}
