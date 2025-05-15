/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   minishell.h                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/08 13:23:31 by hogu           #+#    #+#                */
/*   Updated: 2025/05/08 13:23:32 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>

extern volatile sig_atomic_t	g_signal_received;

typedef struct	s_cmd
{
	char			**args;	// command, options, arguments e.g.{"ls", "-l", NULL}
	char 			*path;	// path for command
	int				is_builtin; // whether or not a buildin cmd (e.g. cd, echo)
	int				pid;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_builtin_type
{
	NON_BUILTIN = 0,
	BUILTIN_ECHO,
	BUILTIN_CD,
	BUILTIN_PWD,
	BUILTIN_EXPORT,
	BUILTIN_UNSET,
	BUILTIN_ENV,
	BUILTIN_EXIT
}	t_builtin_type;

void	signal_handler(int sig);
void	input_loop(void);
void	execute(t_cmd *cmd, char **envp);
int	ft_strcmp(char *s1, char *s2);
void	find_path(t_cmd *cmd, char **envp);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	run_builtin(t_cmd *cmd);
void	echo_builtin(t_cmd *cmd);
void	print_cmd_error(t_cmd *cmd);


#endif
