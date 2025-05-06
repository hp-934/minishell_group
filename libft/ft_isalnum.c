/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:53:08 by hogu              #+#    #+#             */
/*   Updated: 2024/09/12 22:53:09 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

// #include <ctype.h>
// #include <stdio.h>

// int main(void)
// {
// 	char c = '3';
// 	printf("%c, %d\n", c, isalnum(c));
// 	printf("%c, %d\n", c, ft_isalnum(c));
// 	return (0);
// }