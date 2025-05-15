/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/15 17:43:39 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *str)
{
	int		count;
	char	quote;

	count = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (!*str)
			break ;
		count++;
		if (*str == '\'' || *str == '"')
		{
			quote = *str++;
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				str++;
		}
		else
			while (*str && !ft_isspace(*str) && *str != '\'' && *str != '"')
				str++;
	}
	return (count);
}
