/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:15:27 by hogu              #+#    #+#             */
/*   Updated: 2025/05/15 16:45:59 by yaepark          ###   ########.fr       */
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
