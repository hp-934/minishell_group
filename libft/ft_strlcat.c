/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:42:10 by hogu              #+#    #+#             */
/*   Updated: 2024/09/16 10:42:11 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	i = 0;
	while (i < dstsize - dst_len - 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// int	main(void)
// {
// 	char dst1[10] = "one12";
// 	char src1[] = "two";
// 	printf("%lu, %s\n", strlcat(dst1, src1, 6), dst1);

// 	char dst2[10] = "one12";
// 	char src2[] = "two";
// 	printf("%lu, %s\n", ft_strlcat(dst2, src2, 6), dst2);
// }
