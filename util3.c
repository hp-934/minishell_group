/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:05:51 by hogu              #+#    #+#             */
/*   Updated: 2025/06/11 16:05:53 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_identifier(char *str, int *exit_value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		print_builtin_error(BUILTIN_EXPORT, str);
		*exit_value = 1;
		return (0);
	}
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '=')
		{
			print_builtin_error(BUILTIN_EXPORT, str);
			*exit_value = 1;
			return (0);
		}
	}
	return (1);
}
