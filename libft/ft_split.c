/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:33:08 by hogu              #+#    #+#             */
/*   Updated: 2024/09/27 14:33:09 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_result(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
}

static int	count_substring(char const *s, char c)
{
	int	in_substring;
	int	count;

	in_substring = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
			in_substring = 0;
		s++;
	}
	return (count);
}

static int	copy_substrings(char **result, int count, char const *s, char c)
{
	int	i;
	int	len_sub;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		len_sub = 0;
		while (s[len_sub] && s[len_sub] != c)
			len_sub++;
		result[i] = ft_substr(s, 0, len_sub);
		if (!result[i])
		{
			free_result(result, i - 1);
			return (0);
		}
		s += len_sub;
		i++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		count;

	if (!s)
		return (NULL);
	count = count_substring(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	if (!copy_substrings(result, count, s, c))
		return (NULL);
	return (result);
}

// int	main(void)
// {
// 	char const s[] = "*1**234*5 6*";
// 	char c = '*';
// 	printf("%d\n", count_substring(s, c));
// 	char **result = ft_split(s, c);
// 	for (int i = 0; result[i]; i++)
// 		printf("%s\n", result[i]);
// 	free_result(result, count_substring(s, c) - 1);
// 	return (0);
// }
