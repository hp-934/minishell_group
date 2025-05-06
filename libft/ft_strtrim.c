/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:16:23 by hogu              #+#    #+#             */
/*   Updated: 2024/09/27 13:16:24 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;

	if (!s1 || !set)
		return (NULL);
	while ((*s1 && ft_strchr(set, *s1)))
		s1++;
	s1_len = ft_strlen((char *)s1);
	if (s1_len == 0)
		return (ft_strdup(""));
	while (s1_len > 0 && ft_strchr(set, s1[s1_len - 1]))
		s1_len--;
	return (ft_substr(s1, 0, s1_len));
}

// int	main(void)
// {
// 	char const s1[] = "^**closed*^*today**^";
// 	char const s2[] = "^*";
// 	char *result = ft_strtrim(s1, s2);
// 	printf("%s\n", result);
// 	free(result);
// 	return (0);
// }
