/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:47:20 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/23 13:04:50 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	bool	start_single;
	bool	start_double;

	start_single = false;
	start_double = false;
	while (*str)
	{
		if (*str == '\'' && !start_double)
			start_single = !start_single;
		else if (*str == '"' && !start_single)
			start_double = !start_double;
		else if (*str == '\\' || *str == ';')
		{
			if (!start_single && !start_double)
				return (write_error(ERROR_SYNTAX));
		}
		str++;
	}
	if (start_single || start_double)
		return (write_error(ERROR_SYNTAX));
	return (EXIT_SUCCESS);
}

int	check_pipes(char *str)
{
	char	quote;

	str = skip_spaces(str);
	if (*str == '|')
		return (write_error(ERROR_PIPES));
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str++;
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				str++;
		}
		else if (*str == '|')
		{
			str++;
			str = skip_spaces(str);
			if (!*str || *str == '|')
				return (write_error(ERROR_PIPES));
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
