/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   builtin_others.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/07/11 13:49:44 by hogu           #+#    #+#                */
/*   Updated: 2025/07/11 13:49:45 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_env *env)
{
	char	*logical;
	char	*cwd;

	logical = ft_getenv("PWD", env);
	if (logical)
	{
		ft_putendl_fd(logical, STDOUT_FILENO);
		set_exit_status(0);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		set_exit_status(1);
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	set_exit_status(0);
}

void	env_builtin(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	set_exit_status(0);
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

int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] != '-')
		return (0);
	i = 1;
	if (str[i] == '\0')
		return (0);
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	echo_builtin(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (cmd->args[i] && is_n_flag(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	set_exit_status(0);
}
