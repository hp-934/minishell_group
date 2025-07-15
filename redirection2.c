/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:22:27 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/27 16:03:34 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token_and_delimiter(char ***args)
{
	int		i;
	int		j;

	i = 0;
	while ((*args)[i])
	{
		if (ft_strncmp((*args)[i], "<<", 2) == 0)
		{
			j = 2;
			while (j > 0 && (*args)[i])
			{
				free_and_null(&(*args)[i]);
				(*args)[i++] = ft_strdup("");
				j--;
			}
			break ;
		}
		else
			i++;
	}
}

char	*get_delimiter(char **array)
{
	char	*delimiter;
	int		i;

	delimiter = NULL;
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], "<<", 2) == 0 && array[i + 1])
		{
			delimiter = ft_strdup(array[i + 1]);
			remove_token_and_delimiter(&array);
			break ;
		}
		i++;
	}
	return (delimiter);
}

int	heredoc_output(t_cmd **commands, int read_fd)
{
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = read_fd;
	return (EXIT_SUCCESS);
}
