/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:46:28 by hogu              #+#    #+#             */
/*   Updated: 2024/09/28 11:46:29 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		int_len;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	int_len = intlen(n);
	num = (char *)malloc(sizeof(char) * (int_len + 1));
	if (!num)
		return (NULL);
	num[int_len] = '\0';
	if (n < 0)
	{
		num[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		num[--int_len] = n % 10 + '0';
		n = n / 10;
	}
	return (num);
}

// int	main(void)
// {
// 	int	n = -2147483647;
// 	char *num = ft_itoa(n);
// 	printf("%s\n", num);
// 	free(num);
// }