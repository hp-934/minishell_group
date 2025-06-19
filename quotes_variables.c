/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:24:41 by yaepark           #+#    #+#             */
/*   Updated: 2025/06/19 18:42:50 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[i] && !ft_isspace(str[i]) && str[i] != '$' && str[i] != '"'
		&& str[i] != '\'')
		i++;
	tmp = ft_substr(str, start, i - start);
	value = ft_getenv(tmp, env);
	free_and_null(&tmp);
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

char	*fd_to_str(void)
{
	char	*new;
	char	*tmp;
	ssize_t	size;
	char	buffer[BUFFER_SIZE + 1];
	int		fd;

	fd = open(TMP_FILE, O_RDONLY);
	if (fd == -1)
		return (print_parser_error(NULL, ERROR_FILE, NULL), NULL);
	new = NULL;
	tmp = NULL;
	size = read(fd, buffer, BUFFER_SIZE);
	if (size == 0)
		return (ft_strdup(""));
	while (size > 0)
	{
		buffer[size] = '\0';
		tmp = create_or_join_str(buffer, new);
		if (!tmp)
			break ;
		new = tmp;
		size = read(fd, buffer, BUFFER_SIZE);
	}
	close(fd);
	if (!tmp || size == -1)
		free_and_null(&new);
	if (unlink(TMP_FILE) != 0)
		free_and_null(&new);
	return (new);
}

char	*handle_invalid_variable(int fd)
{
	close(fd);
	if (unlink(TMP_FILE) != 0)
		perror("Unlink failed");
	return (NULL);
}

char	*remove_quotes_expand_variables(char *str, t_env *env)
{
	int		i;
	int		fd;
	bool	in_single;
	bool	in_double;

	if (!str || !*str)
		return (ft_strdup(""));
	if (!ft_strchr(str, '$') && !ft_strchr(str, '\'') && !ft_strchr(str, '"'))
		return (ft_strdup(str));
	i = 0;
	in_single = false;
	in_double = false;
	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (print_parser_error(NULL, ERROR_FILE, NULL), NULL);
	if ((str[0] == '\'' || str[0] == '"') && str[0] == str[1] && !str[2])
		return(ft_putchar_fd(' ', fd), fd_to_str());
	while (str[i])
	{
		if (!in_single && !in_double && str[i] == '$' && str[i + 1] == '"')
		{
			i += 2;
			while (str[i] && str[i] != '"')
				ft_putchar_fd(str[i++], fd);
			if (str[i] == '"')
				i++;
			continue;
		}
		if (toggle_quotes(str[i], &in_single, &in_double) == true)
			i++;
		else if (str[i] == '$' && !in_single)
			i = put_variable(str, fd, i, env);
		else
			ft_putchar_fd(str[i++], fd);
	}
	close(fd);
	return (fd_to_str());
}