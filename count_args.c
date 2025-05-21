/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/21 11:48:10 by yaepark          ###   ########.fr       */
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
		while (*str && !ft_isspace(*str))
		{
			if (*str == '\'' || *str == '"')
			{
				quote = *str;
				str++;
				str = ft_strchr(str, quote);
				if (!*str)
					break;
			}
			str++;
		}
	}
	return (count);
}
