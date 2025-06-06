/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:48:10 by hogu              #+#    #+#             */
/*   Updated: 2025/05/23 13:48:11 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_and_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

char	*split_name_value(char *str, char **value)
{
	char	*name;
	char	*eq;
	int		name_len;

	eq = ft_strchr(str, '=');
	if (eq)
	{
		name_len = eq - str;
		name = ft_substr(str, 0, name_len);
		if (!name)
			return (*value = NULL, NULL);
		*value = ft_strdup(eq + 1);
		if (!*value)
			return (free(name), NULL);
	}
	else
	{
		*value = NULL;
		name = strdup(str);
		if (!name)
			return (NULL);
	}
	return (name);
}

long	accumulate_digits(char *s, int neg, char **endptr)
{
	long	result;
	long	cutoff;
	int		cutlim;
	int		digit;

	result = 0;
	cutoff = LONG_MAX / 10;
	cutlim = LONG_MAX % 10;
	while (*s >= '0' && *s <= '9')
	{
		digit = *s - '0';
		if (result > cutoff || (result == cutoff && digit > cutlim))
		{
			errno = ERANGE;
			if (neg == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + digit;
		s++;
	}
	if (endptr)
		*endptr = (char *)s;
	return (result);
}

char	*ft_skip(char *s, int *neg)
{
	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*neg = -1;
		s++;
	}
	return (s);
}

long	ft_strtol(char *str, char **endptr)
{
	char	*s;
	int		neg;
	long	result;

	neg = 1;
	result = 0;
	s = ft_skip(str, &neg);
	if (!(*s >= '0' && *s <= '9'))
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	result = accumulate_digits(s, neg, endptr);
	if (errno == ERANGE)
		return (result);
	else
		return (neg * result);
}
