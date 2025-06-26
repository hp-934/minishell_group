/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   heredoc.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/26 13:22:32 by hogu           #+#    #+#                */
/*   Updated: 2025/06/26 13:22:33 by hogu           ########   odam.nl        */
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

static int	heredoc_read_loop(int fd, char *delim, t_env *env)
{
	int	ret;

	while (!g_signal)
	{
		ret = heredoc_input(fd, delim, env);
		if (ret == EOF_HEREDOC)
			return (EOF_HEREDOC);
		if (ret == ERROR_HEREDOC)
			return (ERROR_HEREDOC);
	}
	return (ERROR_HEREDOC);
}

void	parse_heredoc_input(char *str, char *delimiter, int fd, t_env *env)
{
	int	j;

	j = 0;
	while (str[j])
	{
		while (str[j] && str[j] != '$')
			ft_putchar_fd(str[j++], fd);
		if (str[j] == '$')
		{
			if (*delimiter == '"' || *delimiter == '\'')
				ft_putchar_fd(str[j++], fd);
			else
				j = put_variable(str, fd, j, env);
		}
	}
}

int	heredoc_input(int fd, char *delimiter, t_env *env)
{
	char	*str;
	char	*dequoted_delimiter;

	str = readline(">");
	if (!str)
		return (close(fd), unlink(TMP_FILE), ERROR_HEREDOC);
	add_history(str);
	dequoted_delimiter = remove_quotes_str(delimiter);
	if (ft_strcmp(str, dequoted_delimiter) == 0)
	{
		free_and_null(&str);
		return (EOF_HEREDOC);
	}
	parse_heredoc_input(str, delimiter, fd, env);
	ft_putchar_fd('\n', fd);
	free_and_null(&str);
	free_and_null(&dequoted_delimiter);
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_cmd **commands, char **array, t_env *env)
{
	int		fd;
	char	*delimiter;
	int		return_value;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	delimiter = get_delimiter(array);
	if (!delimiter)
		return (init_signals(), SUCCESS_HEREDOC);
	fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (free_and_null(&delimiter), init_signals(), ERROR_FILE);
	return_value = heredoc_read_loop(fd, delimiter, env);
	close(fd);
	if (return_value == ERROR_HEREDOC || g_signal == 2)
		return (unlink(TMP_FILE), free_and_null(&delimiter), init_signals(),
			g_signal = 0, ERROR_HEREDOC);
	free_and_null(&delimiter);
	init_signals();
	if (heredoc_output(commands) == ERROR_FILE)
		return (ERROR_FILE);
	if (return_value == EOF_HEREDOC)
		return (handle_heredoc(commands, array, env));
	return (SUCCESS_HEREDOC);
}
