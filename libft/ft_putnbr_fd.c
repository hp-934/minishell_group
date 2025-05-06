/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:14:53 by hogu              #+#    #+#             */
/*   Updated: 2024/09/29 12:14:54 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_putnbr_fd(int n, int fd)
// {
// 	char	*nbr;

// 	nbr = ft_itoa(n);
// 	if (!nbr)
// 		return ;
// 	ft_putstr_fd(nbr, fd);
// 	free(nbr);
// }

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

// int	main(void)
// {
// 	int n = -214748364;
// 	ft_putnbr_fd(n, 1);
// }