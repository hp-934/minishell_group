/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:57 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/20 18:45:03 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error(int error)
{
	int	fd;

	fd = STDERR_FILENO;
	if (error == ERROR_SYNTAX)
		write(fd, "Invalid character or quotes\n", 28);
	if (error == ERROR_VAR)
		write(fd, "Invalid variable\n", 17);
	return (EXIT_FAILURE);
}
