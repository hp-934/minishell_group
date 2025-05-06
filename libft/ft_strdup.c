/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:23 by hogu              #+#    #+#             */
/*   Updated: 2024/09/26 19:03:58 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (0);
	i = 0;
	while (i <= len)
	{
		copy[i] = s1[i];
		i++;
	}
	return (copy);
}

// int	main(void)
// {
// 	const char	original[] = "twice";
// 	char	*copy = ft_strdup(original);
// 	printf("%s, %p\n", original, (void *)original);
// 	printf("%s, %p\n", copy, (void *)copy);
// 	free(copy);
// 	return (0);
// }
