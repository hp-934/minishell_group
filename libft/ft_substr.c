/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:26:17 by hogu              #+#    #+#             */
/*   Updated: 2024/09/26 19:26:18 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

// int	main(void)
// {
// 	char const str[] = "Coconut";
// 	char	*sub;

// 	//normal: should return "onu"
// 	sub = ft_substr(str, 3, 3);
// 	printf("%s\n", sub);
// 	free(sub);

// 	//start bigger than s_len: should return "NULL"
// 	sub = ft_substr(str, 8, 3);
// 	printf("%s\n", sub);
// 	free(sub);

// 	//start + len bigger than s_len: should return "t"
// 	sub = ft_substr(str, 6, 3);
// 	printf("%s\n", sub);
// 	free(sub);
// 	return (0);
// }