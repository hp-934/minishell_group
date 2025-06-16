/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:47:20 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/27 14:30:58 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	toggle_quotes(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
	else
		return (false);
	return (true);
}

char	*after_quote(char *str)
{
	char	quote;

	quote = *str++;
	while (*str && *str != quote)
		str++;
	if (*str == quote)
		str++;
	return (str);
}

int	check_quotes(char *str)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	while (*str)
	{
		if (*str == '\'' && !in_double)
			in_single = !in_single;
		else if (*str == '"' && !in_single)
			in_double = !in_double;
		else if (*str == '\\' || *str == ';')
		{
			if (!in_single && !in_double)
				return (write_error(NULL, ERROR_SYNTAX, NULL));
		}
		str++;
	}
	if (in_single || in_double)
		return (write_error(NULL, ERROR_SYNTAX, NULL));
	return (EXIT_SUCCESS);
}

int	check_pipes(char *str)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	str = skip_spaces(str);
	if (*str == '|')
		return (write_error(NULL, ERROR_PIPES, NULL));
	while (*str)
	{
		if (*str == '\'' && !in_double)
			in_single = !in_single;
		else if (*str == '"' && !in_single)
			in_double = !in_double;
		if (*str == '|' && !in_single && !in_double)
		{
			str++;
			str = skip_spaces(str);
			if (!*str || *str == '|')
				return (write_error(NULL, ERROR_PIPES, NULL));
		}
		else
			str++;
	}
	return (EXIT_SUCCESS);
}

int	check_syntax(char *str)
{
	if (check_quotes(str) == EXIT_SUCCESS && check_pipes(str) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
