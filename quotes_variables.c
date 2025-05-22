/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:41 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/22 18:27:35 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_variable(char *str, int fd, int i)
{
	int		start;
	char	*tmp;
	char	*value;

	start = ++i;
	if (str[start] == '?')
	{
		tmp = ft_itoa(get_exit_status());
		if (!tmp)
			return (0);
		ft_putstr_fd(tmp, fd);
		free_and_null(&tmp);
		i++;
		return (i);
	}
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$' && str[i] != '"'
		&& str[i] != '\'')
		i++;
	tmp = ft_substr(str, start, i - start);
	value = getenv(tmp);
	free_and_null(&tmp);
	if (!value)
		return (write_error(ERROR_VAR), 0);
	ft_putstr_fd(value, fd);
	return (i);
}

char	*create_or_join_str(char *buffer, char *new)
{
	char	*tmp;

	if (!new)
	{
		new = ft_strdup(buffer);
		if (!new)
			return (NULL);
	}
	else
	{
		tmp = ft_strjoin(new, buffer);
		free_and_null(&new);
		if (!tmp)
			return (NULL);
		new = tmp;
	}
	return (new);
}

char	*fd_to_str(int fd)
{
	char	*new;
	char	*tmp;
	ssize_t	size;
	char	buffer[BUFFER_SIZE];

	fd = open("var.txt", O_RDONLY);
	if (fd == -1)
		return (NULL);
	new = NULL;
	size = read(fd, buffer, BUFFER_SIZE - 1);
	while (size > 0)
	{
		buffer[size] = '\0';
		tmp = create_or_join_str(buffer, new);
		if (!tmp)
			break;
		new = tmp;
		size = read(fd, buffer, BUFFER_SIZE - 1);
	}
	if (size == -1)
		free_and_null(&new);
	close(fd);
	if (unlink("var.txt") != 0)
		return (perror("Unlink failed"), free_and_null(&new), NULL);
	return (new);
}

int	rm_quote_and_putchar(char *str, int i, int fd)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		ft_putchar_fd(str[i++], fd);
	if (str[i] == quote)
		i++;
	return (i);
}

char	*handle_invalid_variable(int fd)
{
	close(fd);
	if (unlink("var.txt") != 0)
		perror("Unlink failed");
	return (NULL);
}

char	*remove_quotes_expand_variables(char *str)
{
	int		i;
	int		fd;
	char	quote;

	i = 0;
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (ft_strdup(str));
	fd = open("var.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("Error: Open"), NULL);
	while (str[i])
	{
		if (str[i] == '\'')
			i = rm_quote_and_putchar(str, i, fd);
		else if (str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
			{
				if (str[i] == '$')
				{
					i = put_variable(str, fd, i);
					if (i == 0)
						return (handle_invalid_variable(fd));
				}
				else
					ft_putchar_fd(str[i++], fd);
			}
			if (str[i] == quote)
				i++;
		}
		else if (str[i] == '$')
		{
			i = put_variable(str, fd, i);
			if (i == 0)
				return (handle_invalid_variable(fd));
		}
		else
			ft_putchar_fd(str[i++], fd);
	}
	close(fd);
	return (fd_to_str(fd));
}
