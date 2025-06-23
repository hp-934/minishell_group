/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:41 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/23 19:36:46 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_or_join_str(char *buffer, char *str)
{
	char	*tmp;

	if (!str)
	{
		str = ft_strdup(buffer);
		if (!str)
			return (NULL);
	}
	else
	{
		tmp = ft_strjoin(str, buffer);
		free_and_null(&str);
		if (!tmp)
			return (NULL);
		str = tmp;
	}
	return (str);
}

static char	*read_all_from_fd(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*src;
	char	*dst;
	ssize_t	n;

	dst = NULL;
	n = read(fd, buffer, BUFFER_SIZE);
	if (n == 0)
		return (ft_strdup(""));
	while (n > 0)
	{
		buffer[n] = '\0';
		src = create_or_join_str(buffer, dst);
		if (!src)
			return (free_and_null(&dst), NULL);
		dst = src;
		n = read(fd, buffer, BUFFER_SIZE);
	}
	if (n == -1)
		return (free_and_null(&dst), NULL);
	if (!dst)
		dst = ft_strdup("");
	return (dst);
}

char	*fd_to_str(void)
{
	char	*res;
	int		fd;

	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (print_parser_error(NULL, ERROR_FILE, NULL), NULL);
	res = read_all_from_fd(fd);
	close(fd);
	if (unlink(TMP_FILE) != 0)
		return (free_and_null(&res), NULL);
	return (res);
}
