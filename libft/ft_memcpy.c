/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:55:55 by hogu              #+#    #+#             */
/*   Updated: 2024/09/13 15:55:57 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == src || !n)
		return (dst);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

// int	main(void)
// {
// 	//test 1: no overlap
// 	char dst[] = "NULL";
// 	const void	*src = "";
// 	memcpy(dst, src, 5);
// 	printf("%s\n", dst);

// 	//test 2: src < dst < src + len
// 	char src2[] = "monkey";
// 	ft_memcpy(src2 + 2, src2, 4);
// 	printf("%s\n", src2 + 2); // expected: "momo"
// }