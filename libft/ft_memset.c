/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:00:13 by hogu              #+#    #+#             */
/*   Updated: 2024/09/13 12:00:14 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_char;
	size_t			i;

	b_char = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		b_char[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// int	main(void)
// {
// 	int	c = 'r';
// 	size_t	len = 10;
// 	void *space = (void *)malloc(sizeof(char) * (len + 1));
// 	if (!space)
// 		return (0);
// 	ft_memset(space, c, len);
// 	((char *)space)[len] = '\0';
// 	printf("%s\n", (char *)space);
// 	free(space);
// 	return (0);
// }