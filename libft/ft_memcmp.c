/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:30:54 by hogu              #+#    #+#             */
/*   Updated: 2024/09/20 16:30:57 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;
	size_t			i;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] == cs2[i])
			i++;
		else
			return (cs1[i] - cs2[i]);
	}
	return (0);
}

// int	main(void)
// {
// 	const void *s1 = "apple";
// 	const void *s2 = "apple3";
// 	printf("%d\n", memcmp(s1, s2, 5));
// 	printf("%d\n", ft_memcmp(s1, s2, 5));
// }