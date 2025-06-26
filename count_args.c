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

static char	*skip_redir(char *s, int *count)
{
	char	c;

	c = *s;
	while (*s == c)
		s++;
	(*count)++;
	return (s);
}

static char	*skip_token(char *s)
{
	while (*s && !ft_isspace(*s))
	{
		if (*s == '\'' || *s == '"')
			s = after_quote(s);
		else if (is_redirection(s))
			break ;
		else
			s++;
	}
	return (s);
}

int	count_args(char *str)
{
	int		count;

	count = 0;
	while (*str)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
		if (is_redirection(str))
		{
			str = skip_redir(str, &count);
			continue ;
		}
		count++;
		str = skip_token(str);
	}
	return (count);
}
