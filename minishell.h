/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:52:18 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/22 17:19:28 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include "exit_status.h"

# include <stdbool.h>

# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>

# define BLANK -1
# define ERROR_SYNTAX 1
# define ERROR_VAR 2
# define ERROR_PIPES 3
# define BUFFER_SIZE 100

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
	char			**args; // command/options/arguments e.g.{"ls", "-l", NULL}
	char			*path; // path for command
	int				is_builtin; // whether or not a builtin cmd (e.g. cd, echo)
	int				input_fd; // set to -1 if not exist
	int				output_fd; // set to -1 if not exist
	int				pid; // ignore this in parser
	struct s_cmd	*next;
}				t_cmd;

//utils
void	free_arrays(void **array);
void	clear_t_cmd(t_cmd **command);
t_cmd	*t_cmd_new_empty(void);
void	print_char_array(char **str);

//spaces
bool	ft_isspace(char c);
char	*skip_spaces(char *str);

//check_sytax
int		check_syntax(char *str);

//write_errors
int		write_error(int error);

//counting
int		count_args(char *str);
int		count_commands(char *str);

#endif