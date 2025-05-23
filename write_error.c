/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:57 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/23 13:16:05 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error(int error)
{
	int	fd;

	fd = STDERR_FILENO;
	if (error == ERROR_SYNTAX)
		write(fd, "Invalid character or quotes\n", 28);
	else if (error == ERROR_VAR)
		write(fd, "Invalid variable\n", 17);
	else if (error == ERROR_PIPES)
		write(fd, "Invalid pipe '|' syntax\n", 24);
	return (EXIT_FAILURE);
}
