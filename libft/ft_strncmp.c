/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:49:40 by hogu              #+#    #+#             */
/*   Updated: 2024/09/18 14:49:42 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(void)
// {
// 	const char s1[] = "apple";
// 	const char s2[] = "apq33";
// 	printf("%d\n", strncmp(s1, s2, 5));
// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	printf("%d\n", strncmp(s1, s2, 2));
// 	printf("%d\n", ft_strncmp(s1, s2, 2));
// }