/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/23 17:52:16 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char *str)
{
	int		count;

	count = 1;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			str = after_quote(str);
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
