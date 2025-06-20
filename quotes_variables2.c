/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:48:16 by hogu              #+#    #+#             */
/*   Updated: 2025/06/20 13:22:23 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_dollar_quote(char *str, int fd, int i)
{
	i += 2;
	while (str[i] && str[i] != '"')
		ft_putchar_fd(str[i++], fd);
	if (str[i] == '"')
		i++;
	return (i);
}

int	init_expand_state(char *str, int *fd)
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
