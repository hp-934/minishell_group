/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:50:12 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/27 15:01:21 by yaepark          ###   ########.fr       */
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
		array[i] = NULL;
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
		if ((*command)->args)
			free_arrays((void **)(*command)->args);
		if ((*command)->path)
			free_and_null(&(*command)->path);
		free(*command);
		*command = temp;
	}
	*command = NULL;
}

t_cmd	*t_cmd_new_empty(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->path = NULL;
	new->next = NULL;
	new->is_builtin = NON_BUILTIN;
	new->input_fd = -1;
	new->output_fd = -1;
	new->pid = -1;
	return (new);
}

void	print_char_array(char **str)
{
	static int	count = 1;

	if (!str)
		return ;
	printf("[command %d]\n", count);
	while (*str)
	{
		printf("%s\n", *str);
		str++;
	}
	count++;
}

void	free_and_null(char **str)
{
	if (!*str)
		return ;
	free(*str);
	*str = NULL;
}
