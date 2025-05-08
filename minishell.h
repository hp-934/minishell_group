/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:52:18 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/06 14:52:05 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

//for printf, perror
# include <stdio.h>

//for strerror
#include <string.h>

//for readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
// add_history
# include <readline/readline.h>
# include <readline/history.h>

//for malloc, free, exit, getenv
# include <stdlib.h>

//for write, read, access, close, open, dup, dup2, pipe, isatty, ttyname,
// ttyslot, getcwd, chdir, execve
# include <fcntl.h>
# include <unistd.h>

//for fork, wait, waitpid, wait3, wait4, kill
# include <sys/types.h>
# include <sys/wait.h>

//for signal, sigaction, sigemptyset, sigaddset
# include <signal.h>

//for stat, lstat, fstat, unlink
# include <sys/stat.h>

//for opendir, readdir, closedir
# include <dirent.h>

//for tcsetattr, tcgetattr, ioctl
#include <termios.h>
#include <sys/ioctl.h>

//for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termcap.h>

#endif