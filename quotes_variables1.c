/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:41 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/20 13:53:24 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_value(char *str, int *i, t_env *env)
{
	int		start;
	char	*key;
	char	*value;

	start = *i;
	while (str[*i] && !ft_isspace(str[*i]) && str[*i] != '$'
		&& str[*i] != '"' && str[*i] != '\'' && str[*i] != '/')
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		return (NULL);
	value = ft_getenv(key, env);
	free_and_null(&key);
	return (value);
}

int	put_variable(char *str, int fd, int i, t_env *env)
{
	int		start;
	char	*tmp;
	char	*value;

	start = ++i;
	if (str[start] == '\0' || str[start] == '"' || ft_isspace(str[start]))
	{
		ft_putchar_fd('$', fd);
		while (str[start] && ft_isspace(str[start]))
			ft_putchar_fd(str[start++], fd);
		return (start);
	}
	if (str[start] == '?')
	{
		tmp = ft_itoa(get_exit_status());
		ft_putstr_fd(tmp, fd);
		free_and_null(&tmp);
		return (++i);
	}
	value = extract_var_value(str, &i, env);
	if (!value)
		ft_putstr_fd("", fd);
	else
		ft_putstr_fd(value, fd);
	return (i);
}

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
