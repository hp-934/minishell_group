/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:16:08 by hogu              #+#    #+#             */
/*   Updated: 2025/06/23 20:19:45 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_by_pipes(char *str, int count)
{
	int		i;
	char	**split;
	char	*end;

	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	i = 0;
	end = str;
	while (*end)
	{
		if (*end == '\'' || *end == '"')
			end = after_quote(end);
		else if (*end == '|')
		{
			split[i++] = ft_substr(str, 0, end - str);
			end++;
			str = end;
		}
		else
			end++;
	}
	split[i++] = ft_substr(str, 0, end - str);
	split[i] = NULL;
	return (split);
}

static int	save_token(char **dst, char *start, char *end, t_env *env)
{
	size_t	len;
	char	*tmp;

	len = end - start;
	*dst = ft_substr(start, 0, len);
	if (!*dst)
		return (1);
	if (env)
	{
		tmp = expand_variables(*dst, env);
		if (!tmp)
			return (free_and_null(dst), 1);
		free_and_null(dst);
		*dst = tmp;
	}
	return (0);
}

static char	*handle_redir_token(char *str, char **args, int *i)
{
	char	c;
	char	*end;

	c = *str;
	end = str;
	while (*end == c)
		end++;
	if (save_token(&args[(*i)++], str, end, NULL))
		return (NULL);
	return (end);
}

static char	*handle_normal_token(char *str, char **args, int *i, t_env *env)
{
	char	*end;
	char	*tmp;

	end = str;
	while (*end && !ft_isspace(*end) && !is_redirection(end))
	{
		if (*end == '\'' || *end == '"')
			end = after_quote(end);
		else
			end++;
	}
	if (save_token(&tmp, str, end, env))
		return (NULL);
	args[(*i)++] = tmp;
	return (end);
}

static char	*handle_heredoc_token(char *str, char **args, int *i)
{
	str = handle_redir_token(str, args, i);
	if (!str)
		return (free_arrays((void **)args), NULL);
	str = skip_spaces(str);
	if (!*str)
		return (NULL) ;
	str = handle_normal_token(str, args, i, NULL);
	return (str);
}

char	**tokenize_input(char *str, t_env *env)
{
	char	**args;
	int		count;
	int		i;

	count = count_args(str);
	if (!count)
		return (NULL);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		str = skip_spaces(str);
		if (!*str)
			break ;
		if (ft_strncmp("<<", str, 2) == 0)
			str = handle_heredoc_token(str, args, &i);
		else if (is_redirection(str))
			str = handle_redir_token(str, args, &i);
		else
			str = handle_normal_token(str, args, &i, env);
		if (!str)
			return (free_arrays((void **)args), NULL);
		//printf("str: %s\n", str);
	}
	args[i] = NULL;
	return (args);
}
