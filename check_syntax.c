/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:47:20 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/15 17:14:37 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *str)
{
	bool	start_single;
	bool	start_double;

	start_single = false;
	start_double = false;
	while (*str)
	{
		if (*str == '\'')
		{
			if (start_single == false && start_double == false)
				start_single = true;
			else if (start_single == true)
				start_single = false;
		}
		else if (*str == '"')
		{
			if (start_single == false && start_double == false)
				start_double = true;
			else if (start_double == true)
				start_double = false;
		}
		else if (*str == '\\' || *str == ';')
			if (start_single == false && start_double == false)
				return (write_error(ERROR_SYNTAX));
		str++;
	}
	if (start_single == true || start_double == true)
		return (write_error(ERROR_SYNTAX));
	return (EXIT_SUCCESS);
}
