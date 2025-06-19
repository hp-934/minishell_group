/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_strict.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/05/22 14:32:08 by hogu           #+#    #+#                */
/*   Updated: 2025/05/22 14:32:09 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cd_env(t_env *env, char *old_pwd, char *new_pwd)
{
	t_env	*match;
	char	*old;
	char	*new;

	old = ft_strdup("OLDPWD");
	new = ft_strdup("PWD");
	match = search_node(old, env);
	if (match)
		replace_node(old, old_pwd, match);
	else
		append_node(old, old_pwd, env);
	match = search_node(new, env);
	if (match)
		replace_node(new, new_pwd, match);
	else
		append_node(new, new_pwd, env);
}

void	cd_builtin(t_cmd *cmd, t_env *env)
{
	char	*old_pwd;
	char	*new_pwd;

	if (!cmd->args[1] || !cmd->args[1][0])
	{
		ft_putendl_fd("cd: usage: cd <path>", STDERR_FILENO);
		return ((void)set_exit_status(1));
	}
	else if (cmd->args[2])
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		return ((void)set_exit_status(1));
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(cmd->args[1]) == -1)
	{
		if (old_pwd)
			free(old_pwd);
		print_builtin_error(cmd->is_builtin, cmd->args[1]);
		return ((void)set_exit_status(1));
	}
	new_pwd = getcwd(NULL, 0);
	update_cd_env(env, old_pwd, new_pwd);
	set_exit_status(0);
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
			replace_node(name, value, match);
		else
			append_node(name, value, env);
	}
	if (i == 1)
		print_env_az(env);
	set_exit_status(exit_value);
}

void	unset_builtin(t_cmd *cmd, t_env **env_head)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		remove_node(env_head, cmd->args[i]);
		i++;
	}
	set_exit_status(0);
}

int	exit_builtin(t_cmd *cmd)
{
	char	*endptr;
	long	value;
	int		exitcode;

	if (!cmd->next && isatty(STDOUT_FILENO))
		printf("exit\n");
	if (!cmd->args[1])
	{
		g_signal = 1;
		return (set_exit_status(0));
	}
	errno = 0;
	value = ft_strtol(cmd->args[1], &endptr);
	if (*endptr != '\0' || errno == ERANGE)
		return (print_builtin_error(cmd->is_builtin, cmd->args[1]), 0);
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (set_exit_status(1));
	}
	exitcode = (int)(value % 256);
	if (exitcode < 0)
		exitcode += 256;
	g_signal = 1;
	return (set_exit_status(exitcode));
}
