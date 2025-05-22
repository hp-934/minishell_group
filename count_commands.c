/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/22 15:39:31 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands (char *str)
{
	int		count;
	char	quote;

	count = 1;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				str++;
		}
		else if (*str == '|')
		{
			count++;
			str++;
		}
		else
			str++;
	}
	return (count);
}
