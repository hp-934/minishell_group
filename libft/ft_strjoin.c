/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:09:34 by hogu              #+#    #+#             */
/*   Updated: 2024/09/27 10:09:35 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	s1_len;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	len = s1_len + ft_strlen(s2);
	joined = (char *)malloc(len + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		joined[i] = s1[i];
	i--;
	while (++i < len)
		joined[i] = s2[i - s1_len];
	joined[i] = '\0';
	return (joined);
}

// int	main(void)
// {
// 	char const *s1 = "nice";
// 	char const s2[] = "shirt";
// 	char *result = ft_strjoin(s1, s2);
// 	printf("%s\n", result);
// 	free(result);
// }