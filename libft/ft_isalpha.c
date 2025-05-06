/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:41:12 by hogu              #+#    #+#             */
/*   Updated: 2024/09/11 13:41:13 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	char c = 'd';
// 	printf("%c, %d\n", c, isalpha(c));
// 	printf("%c, %d\n", c, ft_isalpha(c));
// 	return (0);
// }