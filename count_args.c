/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/22 17:05:29 by yaepark          ###   ########.fr       */
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
		str = skip_spaces(str);
		if (!*str)
			break ;
		count++;
		while (*str && !ft_isspace(*str))
		{
			if (*str == '\'' || *str == '"')
			{
				quote = *str++;
				while (*str && *str != quote)
					str++;
				if (*str == quote)
					str++;
			}
			else
				str++;
		}
	}
	return (count);
}
