/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   input.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/08 13:23:16 by hogu           #+#    #+#                */
/*   Updated: 2025/05/08 13:23:17 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_loop(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		if (*line)
			add_history(line);
		printf("<< [%s]\n", line);
		free(line);
	}
}
