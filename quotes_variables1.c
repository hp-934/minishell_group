/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:41 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/19 22:42:23 by yaepark          ###   ########.fr       */
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
			&& str[*i] != '"' && str[*i] != '\'')
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

static int	handle_dollar_quote(char *str, int fd, int i)
{
	i += 2;
	while (str[i] && str[i] != '"')
		ft_putchar_fd(str[i++], fd);
	if (str[i] == '"')
		i++;
	return (i);
}

static int	init_expand_state(char *str, int *fd)
{
	if (!str || !*str)
		return (-1);
	*fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (*fd == -1)
		return (-1);
	return (0);
}

char	*expand_variables(char *str, t_env *env)
{
	int		i;
	int		fd;
	bool	in_single;
	bool	in_double;

	if (!str || !*str)
		return (ft_strdup(""));
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (ft_strdup(str));
	if (init_expand_state(str, &fd) == -1)
		return (print_parser_error(NULL, ERROR_FILE, NULL), NULL);
	i = 0;
	in_single = false;
	in_double = false;
	while (str[i])
	{
		toggle_quotes(str[i], &in_single, &in_double);
		if (!in_single && !in_double && str[i] == '$' && str[i + 1] == '"')
			i = handle_dollar_quote(str, fd, i);
		else if (str[i] == '$' && !in_single)
			i = put_variable(str, fd, i, env);
		else
			ft_putchar_fd(str[i++], fd);
	}
	return (close(fd), fd_to_str());
}
