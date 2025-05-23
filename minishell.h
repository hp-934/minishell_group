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

typedef struct s_cmd
{
	char			**args;
	char			*path;
	int				is_builtin;
	int				pid;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

void	input_loop(void);

//signal
void	signal_handler(int sig);

//find_cmd
void	find_path(t_cmd *cmd, char **envp);

//execute
void	execute(t_cmd *cmd, char **envp);
void	dup2_and_close(int fd1, int fd2);

//builtin
void	run_builtin(t_cmd *cmd, char **envp);
void	echo_builtin(t_cmd *cmd);
void	pwd_builtin(void);
void	env_builtin(char **envp);
void	cd_builtin(t_cmd *cmd);

//print_error
void	print_cmd_error(t_cmd *cmd);

//util
int		ft_strcmp(char *s1, char *s2);
int		has_pipe(t_cmd *cmd);
int		is_strict_builtin(int is_strict_builtin);

#endif
