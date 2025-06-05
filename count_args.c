/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/23 18:01:41 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *str)
{
	int		count;

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
				str = after_quote(str);
			else
				str++;
		}
	}
	return (count);
}
