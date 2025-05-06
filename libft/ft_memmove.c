/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:32:25 by hogu              #+#    #+#             */
/*   Updated: 2024/09/13 16:32:26 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (dst == src)
		return (dst);
	d = (char *)dst;
	s = (const char *)src;
	if (d > s && d < (s + len))
	{
		while (len--)
			*(d + len) = *(s + len);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

// int	main(void)
// {
// 	//test case 1: no overlap
// 	char src1[] = "apple";
// 	char dst1[20];
// 	ft_memmove(dst1, src1, strlen(src1) + 1);
// 	printf("test 1 (no overlap): %s\n", dst1);

// 	//test case 2: overlap, dst < src (low to high copy)
// 	char src2[] = "abcde";
// 	ft_memmove(src2, src2 + 2, strlen(src2 + 2));
// 	printf("test 1 (no overlap): %s\n", src2); // expected: "cdede"

// 	//test case 3: overlap, src < dst < src + len (high to low copy)
// 	char src3[] = "12345";
// 	ft_memmove(src3 + 2, src3, strlen(src3) + 1);
// 	printf("test 1 (no overlap): %s\n", src3 + 2); // expected: "12345"	
// }