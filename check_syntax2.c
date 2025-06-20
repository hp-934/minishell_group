/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   check_syntax2.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/06/20 12:06:07 by hogu           #+#    #+#                */
/*   Updated: 2025/06/20 12:06:08 by hogu           ########   odam.nl        */
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
