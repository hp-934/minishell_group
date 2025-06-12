/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:28:50 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/12 15:27:34 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *str)
{
	int		count;
	char	c;

	count = 0;
	while (*str)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
		if (is_redirection(str))
		{
			c = *str;
			while (*str == c)
				str++;
			count++;
			continue;
		}
		count++;
		while (*str && !ft_isspace(*str))
		{
			if (*str == '\'' || *str == '"')
				str = after_quote(str);
			else if (is_redirection(str))
				break;
			else
				str++;
		}
	}
	return (count);
}
