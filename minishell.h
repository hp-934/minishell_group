/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:23:31 by hogu              #+#    #+#             */
/*   Updated: 2025/06/12 17:32:31 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "exit_status.h"

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# define BLANK -1
# define ERROR_SYNTAX 1
# define ERROR_VAR 2
# define ERROR_PIPES 3
# define ERROR_COMMAND 4
# define ERROR_REDIRECTION 5
# define ERROR_FILE 6
# define ERROR_HEREDOC 7

# define PATH_NOTFOUND "-1"
# define PATH_NOPERM "-2"
# define PATH_ISDIR "-3"
# define ERROR_CMD_NOTFOUND 127
# define ERROR_CMD_ISDIR 126
# define ERROR_CMD_NOPERM 126

# define BUFFER_SIZE 100

# define TMP_FILE "tmp_file.txt"

extern volatile sig_atomic_t	g_signal;

typedef enum e_builtin_type
{
	NON_BUILTIN = 10,
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
	int				redir_error;
	char			*bad_token;
	int				errno_saved;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

//utils
void	free_arrays(void **array);
void	clear_t_cmd(t_cmd **command);
t_cmd	*t_cmd_new_empty(void);
void	free_and_null(char **str);
char	*fd_to_str(void);

//spaces
bool	ft_isspace(char c);
char	*skip_spaces(char *str);

//check_sytax
int		check_syntax(char *str);
int		toggle_quotes(char c, bool *in_single, bool *in_double);
char	*after_quote(char *str);
bool	is_redirection(char *str);

//write_errors
int write_error(char *cmd_name, int error_type, char *token);
//counting
int		count_args(char *str);
int		count_commands(char *str);

//parsing
t_cmd	*parser(char *str, t_env *env);
t_cmd	*handle_redirections(t_cmd **commands);
char	*remove_quotes_expand_variables(char *str, t_env *env);
int		handle_heredoc(t_cmd **commands, char **args, int i);

//print test
void	print_cmd_args(t_cmd *commands);
void	print_char_array(char **str);

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
char	*ft_getenv(char *name, t_env *env);

//signal
void	init_signals(void);
void	refresh_prompt(void);
void	sigint_handler(int sig);
int		handle_eof(void);

//find_cmd
void	find_path(t_cmd *cmd, t_env *env);
void	free_split(char **split);

//execute
void	execute(t_cmd *cmd, t_env **env_head);
void	dup2_and_close(int fd1, int fd2, int fd3);

//builtin
int		check_builtin(char **args);
void	run_builtin(t_cmd *cmd, t_env **env_head);
void	echo_builtin(t_cmd *cmd);
void	pwd_builtin(void);
void	env_builtin(t_env *env);
void	cd_builtin(t_cmd *cmd, t_env *env);
void	export_builtin(t_cmd *cmd, t_env *env);
void	unset_builtin(t_cmd *cmd, t_env **env_head);
int		exit_builtin(t_cmd *cmd);

//print_error
void	print_cmd_error(t_cmd *cmd);
void	print_builtin_error(int builtin, char *str);
void	sig_write_next_line(int sig);

//util
int		ft_strcmp(char *s1, char *s2);
int		has_pipe(t_cmd *cmd);
int		has_redirection(t_cmd *cmd);
int		is_pathless_builtin(int is_builtin);
int		is_must_parent_builtin(t_cmd *cmd);
char	*split_name_value(char *str, char **value);
long	ft_strtol(char *str, char **endptr);
int		valid_identifier(char *str, int *exit_value);
t_cmd	*remove_nul_strs_from_cmd_args(t_cmd **commands);
int		is_n_variant(char *str);

#endif