/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_export.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/10 13:16:01 by hogu           #+#    #+#                */
/*   Updated: 2025/07/10 13:16:02 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_identifier(char *str, int *exit_value)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		print_export_error(str);
		if (*str == '-')
			*exit_value = 2;
		else
			*exit_value = 1;
		return (0);
	}
	while (str[++i] && str[i] != '=')
	{
		if ((str[i] == '+' && str[i + 1] != '=') || (!ft_isalnum(str[i])
				&& str[i] != '_' && str[i] != '=' && str[i] != '+'))
		{
			print_export_error(str);
			*exit_value = 1;
			return (0);
		}
	}
	return (1);
}

int	is_append_mode(char *str)
{
	char	*plus_eq;
	char	*eq;

	if (str)
	{
		plus_eq = ft_strnstr(str, "+=", ft_strlen(str));
		eq = ft_strchr(str, '=');
		if (plus_eq && eq && plus_eq < eq)
			return (1);
	}
	return (0);
}

char	*split_name_value(char *str, char **value)
{
	char	*name;
	char	*eq;
	int		name_len;
	int		mode;

	mode = is_append_mode(str);
	eq = ft_strchr(str, '=');
	if (eq)
	{
		name_len = eq - str - mode;
		name = ft_substr(str, 0, name_len);
		if (!name || name[0] == '\0')
			return (*value = NULL, NULL);
		*value = ft_strdup(eq + 1);
		if (!*value)
			return (free(name), NULL);
	}
	else
	{
		*value = NULL;
		name = strdup(str);
		if (!name || name[0] == '\0')
			return (NULL);
	}
	return (name);
}

void	export_builtin(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*match;
	int		exit_value;

	i = 0;
	exit_value = 0;
	while (cmd->args[++i])
	{
		if (!valid_identifier(cmd->args[i], &exit_value))
			continue ;
		name = split_name_value(cmd->args[i], &value);
		if (!name)
			continue ;
		match = search_node(name, env);
		if (match)
			replace_node(cmd->args[i], name, value, match);
		else
			append_node(name, value, env);
	}
	if (i == 1)
		print_env_az(env);
	set_exit_status(exit_value);
}
