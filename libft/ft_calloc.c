/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:53:02 by hogu              #+#    #+#             */
/*   Updated: 2024/09/25 16:53:06 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*space;

	space = (void *)malloc(count * size);
	if (!space)
		return (0);
	ft_bzero(space, count * size);
	return (space);
}

// int	main(void)
// {
// 	int	*arr = (int *)ft_calloc(10, sizeof(int));
// 	if (!arr)
// 	{
// 		printf("Memory allocation failed.\n");
// 		return (1);
// 	}
// 	for (int i = 0; i < 10; i++)
// 		printf("%d", arr[i]);
// 	free(arr);
// }
