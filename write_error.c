/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:48:57 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/27 17:01:40 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error(int error)
{
	int	fd;

	fd = STDERR_FILENO;
	if (error == ERROR_SYNTAX)
		write(fd, "Invalid quotes or unsupported characters\n", 41);
	else if (error == ERROR_VAR)
		write(fd, "Invalid variable\n", 17);
	else if (error == ERROR_PIPES)
		write(fd, "Invalid pipe '|' syntax\n", 24);
	else if (error == ERROR_COMMAND)
		write(fd, "Empty command\n", 14);
	else if (error == ERROR_REDIRECTION)
		write(fd, "Redirection operator error\n", 27);
	return (EXIT_FAILURE);
}
