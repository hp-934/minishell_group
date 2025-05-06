/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:37:23 by hogu              #+#    #+#             */
/*   Updated: 2024/09/12 22:37:25 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	char c = 'a';
// 	printf("%c, %d\n", c, isdigit(c));
// 	printf("%c, %d\n", c, ft_isdigit(c));
// 	return (0);
// }