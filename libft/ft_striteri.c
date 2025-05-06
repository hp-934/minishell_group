/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:55:03 by hogu              #+#    #+#             */
/*   Updated: 2024/09/29 11:55:05 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	ft_to_upper2(unsigned int i, char *c)
// {
// 	(void) i;
// 	if (*c >= 'a' && *c <= 'z')
// 		*c = *c - 32;
// }

// int	main(void)
// {
// 	char s[] = "Happy Birthday";
// 	printf("%s\n", s);
// 	ft_striteri(s, ft_to_upper2);
// 	printf("%s\n", s);
// 	return (0);
// }