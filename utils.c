/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:50:12 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/15 12:48:00 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arrays(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clear_t_cmd(t_cmd **command)
{
	t_cmd	*temp;

	if (!command || !*command)
		return ;
	while (*command)
	{
		temp = (*command)->next;
		free_arrays((void **)(*command)->args);
		if ((*command)->path)
			free((*command)->path);
		free(*command);
		*command = temp;
	}
	*command = NULL;
}

t_cmd	*t_cmd_new_empty()
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->args = NULL;
	new->path = NULL;
	new->next = NULL;
	return (new);
}

void	print_char_array(char **str)
{
	if (!str)
		return ;
	while (*str)
	{
		printf("%s\n", *str);
		str++;
	}
}

bool ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	else
		return (false);
}