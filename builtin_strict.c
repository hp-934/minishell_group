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

	if (cmd->args[1] && cmd->args[1][0] == '-')
	{
		print_unset_error(cmd->args[1]);
		return ;
	}
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
