/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_exit.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/11 13:47:13 by hogu           #+#    #+#                */
/*   Updated: 2025/07/11 13:47:14 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	handle_overflow(char *s, int neg, char **endptr)
{
	if (endptr)
		*endptr = s;
	if (neg == 1)
	{
		errno = ERANGE;
		return (LONG_MAX);
	}
	else
		return (LONG_MIN);
}

long	accumulate_digits(char *s, int neg, char **endptr)
{
	long	result;
	int		digit;

	result = 0;
	while (*s >= '0' && *s <= '9')
	{
		digit = *s - '0';
		if (result > LONG_MAX / 10 || (result == LONG_MAX / 10
				&& digit > LONG_MAX % 10))
		{
			if (neg == -1 && result == LONG_MAX / 10
				&& digit == LONG_MAX % 10 + 1 && s[1] == '\0')
			{
				result = result * 10 + digit;
				s++;
				break ;
			}
			return (handle_overflow(s, neg, endptr));
		}
		result = result * 10 + digit;
		s++;
	}
	if (endptr)
		*endptr = s;
	return (result);
}

char	*ft_skip(char *s, int *neg)
{
	int		len;

	while (*s && ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*neg = -1;
		s++;
	}
	len = ft_strlen(s);
	while (len - 1 >= 0 && ft_isspace(s[len - 1]))
	{
		s[len - 1] = '\0';
		len--;
	}
	return (s);
}

long	ft_strtol(char *str, char **endptr)
{
	char	*s;
	int		neg;
	long	result;

	result = 0;
	neg = 1;
	s = ft_skip(str, &neg);
	if (!(*s >= '0' && *s <= '9'))
	{
		if (endptr)
			*endptr = str;
		return (0);
	}
	result = accumulate_digits(s, neg, endptr);
	if (errno == ERANGE)
		return (result);
	else
		return (neg * result);
}

int	exit_builtin(t_cmd *cmd)
{
	char	*endptr;
	long	value;
	int		exitcode;

	if (!cmd->next && isatty(STDOUT_FILENO))
		printf("exit\n");
	if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "--"))
	{
		g_signal = 1;
		return (set_exit_status(0));
	}
	errno = 0;
	value = ft_strtol(cmd->args[1], &endptr);
	if (cmd->args[1][0] == '\0' || *endptr != '\0')
		return (print_exit_error(cmd->args[1], EXIT_NON_NUM), 0);
	if (cmd->args[2])
		return (print_exit_error(cmd->args[1], EXIT_TOO_MANY)
			, set_exit_status(1));
	exitcode = (int)(value % 256);
	if (exitcode < 0)
		exitcode += 256;
	g_signal = 1;
	return (set_exit_status(exitcode));
}
