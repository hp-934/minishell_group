/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:47:20 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/17 16:26:27 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				return (print_parser_error(NULL, ERROR_SYNTAX, NULL));
		}
		str++;
	}
	if (in_single || in_double)
		return (print_parser_error(NULL, ERROR_SYNTAX, NULL));
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
		return (print_parser_error(NULL, ERROR_SYNTAX, "|"));
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
				return (print_parser_error(NULL, ERROR_SYNTAX, "|"));
		}
		else
			str++;
	}
	return (EXIT_SUCCESS);
}

static int	check_redir_target(char *str)
{
	str = skip_spaces(str);
	if (*str == '|')
		return (print_parser_error(NULL, ERROR_SYNTAX, "|"));
	if (!*str || is_redirection(str))
		return (print_parser_error(NULL, ERROR_SYNTAX, "newline"));
	return (EXIT_SUCCESS);
}

int	check_redirection(char *str)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	str = skip_spaces(str);
	if (is_redirection(str))
		return (print_parser_error(NULL, ERROR_SYNTAX, "newline"));
	while (*str)
	{
		if (*str == '\'' && !in_double)
			in_single = !in_single;
		else if (*str == '"' && !in_single)
			in_double = !in_double;
		if (is_redirection(str) && !in_single && !in_double)
		{
			str += (*str == *(str + 1)) + 1;
			if (check_redir_target(str) != EXIT_SUCCESS)
				return (EXIT_FAILURE);
			continue ;
		}
		str++;
	}
	return (EXIT_SUCCESS);
}

int	check_syntax(char *str)
{
	if (check_quotes(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_pipes(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_redirection(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
