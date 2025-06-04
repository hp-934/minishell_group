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
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

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

//env
t_env	*init_env(void);
void	free_env(t_env *env);
t_env	*duplicate_envp(char **envp);
char	**format_char_env(t_env *env);
void	print_env_az(t_env *env);
t_env	*search_node(char *target, t_env *env);
void	append_node(char *name, char *value, t_env *env);
void	replace_node(char *name, char *value, t_env *env);
void	remove_node(t_env **head_ptr, char *name);

//signal
void	signal_handler(int sig);

//find_cmd
void	find_path(t_cmd *cmd, t_env *env);
void	free_split(char **split);

//execute
void	execute(t_cmd *cmd, t_env **env_head);
void	dup2_and_close(int fd1, int fd2);

//builtin
int		check_builtin(char **args);
void	run_builtin(t_cmd *cmd, t_env **env_head);
void	echo_builtin(t_cmd *cmd);
void	pwd_builtin(void);
void	env_builtin(t_env *env);
void	cd_builtin(t_cmd *cmd, t_env *env);
void	export_builtin(t_cmd *cmd, t_env *env);
void	unset_builtin(t_cmd *cmd, t_env **env_head);
void	exit_builtin(t_cmd *cmd);

//print_error
void	print_cmd_error(t_cmd *cmd);
void	print_builtin_error(int builtin, char *str);

//util
int		ft_strcmp(char *s1, char *s2);
int		has_pipe(t_cmd *cmd);
int		has_redirection(t_cmd *cmd);
int		is_pathless_builtin(int is_builtin);
int		is_must_parent_builtin(t_cmd *cmd);
char	*split_name_value(char *str, char **value);
long	ft_strtol(char *str, char **endptr);

#endif
