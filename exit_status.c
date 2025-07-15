/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   exit_status.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/13 14:15:27 by hogu           #+#    #+#                */
/*   Updated: 2025/05/13 14:15:28 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"

int	set_exit_status(int code)
{
	static int	status;

	if (code != -1)
		status = code;
	return (status);
}

int	get_exit_status(void)
{
	return (set_exit_status(-1));
}
