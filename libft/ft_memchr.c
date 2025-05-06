/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:53:03 by hogu              #+#    #+#             */
/*   Updated: 2024/09/18 15:53:07 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		n--;
		ptr++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char *s = "literal";
// 	printf("%s\n",(char *)memchr(s, 'l', 1));
// 	printf("%s\n",(char *)ft_memchr(s, 'l', 1));
// }