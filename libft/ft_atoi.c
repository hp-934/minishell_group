/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:07:13 by hogu              #+#    #+#             */
/*   Updated: 2024/09/24 15:07:14 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	neg;

	result = 0;
	neg = 1;
	while ((*str > 8 && *str < 14) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * neg);
}

// int	main(void)
// {
// 	const char new[] = "-+32 1toi4";
// 	printf("%d\n", atoi(new));
// 	printf("%d\n", ft_atoi(new));
// }