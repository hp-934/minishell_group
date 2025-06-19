/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   redirection.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: yaepark <yaepark@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/27 15:39:11 by yaepark		   #+#	#+#			 */
/*   Updated: 2025/06/17 13:12:44 by yaepark		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	redirect_stdin_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (ERROR_SYNTAX);
	file = args[i + 1];
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->input_fd > STDERR_FILENO)
		close((*commands)->input_fd);
	(*commands)->input_fd = fd;
	return (EXIT_SUCCESS);
}

int	redirect_stdout_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (ERROR_SYNTAX);
	file = args[i + 1];
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

int	append_stdout_file(t_cmd **commands, char **args, int i)
{
	char	*file;
	int		fd;

	if (!args[i + 1])
		return (ERROR_SYNTAX);
	file = args[i + 1];
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (ERROR_FILE);
	if ((*commands)->output_fd > STDERR_FILENO)
		close((*commands)->output_fd);
	(*commands)->output_fd = fd;
	return (EXIT_SUCCESS);
}

char	**remove_redirection_from_args(char **args)
{
	int		i;
	int		j;

	i = 0;
	while (args[i])
	{
		if (is_redirection(args[i]))
		{
			if (args[i][1] && args[i][0] != args[i][1])
			{
				i++;
				continue ;
			}
			if (args[i][2] && args[i][0] == args[i][1] && args[i][1]!= args[i][2])
			{
				i++;
				continue ;
			}
			free_and_null(&args[i]);
			if (args[i + 1])
				free_and_null(&args[i + 1]);
			j = i;
			while (args[j + 2])
			{
				args[j] = args[j + 2];
				j++;
			}
			args[j++] = NULL;
			args[j] = NULL;
		}
		else
			i++;
	}
	return (args);
}

int	redirect(t_cmd **commands, char **array, int i, t_env *env)
{
	int	result;

	result = EXIT_SUCCESS;
	if (ft_strncmp(array[i], ">>", 2) == 0)
		result = append_stdout_file(commands, array, i);
	else if (ft_strncmp(array[i], "<<", 2) == 0)
		result = handle_heredoc(commands, array, i, env);
	else if (ft_strncmp(array[i], ">", 1) == 0)
		result = redirect_stdout_file(commands, array, i);
	else if (ft_strncmp(array[i], "<", 1) == 0)
		result = redirect_stdin_file(commands, array, i);
	return (result);
}

t_cmd	*handle_redirections(t_cmd **commands, t_env *env)
{
	char	**array;
	int		i;
	int		result;
	t_cmd	*cmd_top;

	cmd_top = *commands;
	while (cmd_top)
	{
		array = cmd_top->args;
		i = 0;
		while (array[i] && cmd_top->redir_error == 0)
		{
			if (is_redirection(array[i]) && array[i][1] && array[i][0] != array[i][1])
			{
				i++;
				continue ;
			}
			result = redirect(&cmd_top, array, i, env);
			if (result)
			{
				if (result == SUCCESS_HEREDOC)
					break ;
				cmd_top->redir_error = result;
				if (result == ERROR_REDIRECTION)
					cmd_top->bad_token = ft_strdup(array[i]);
				else if (result == ERROR_FILE)
				{
					cmd_top->bad_token = ft_strdup(array[i + 1]);
					cmd_top->errno_saved = errno;
				}
				else
					cmd_top->bad_token = ft_strdup(array[i]);
			}
			i++;
		}
		array = remove_redirection_from_args(array);
		cmd_top = cmd_top->next;
	}
	return (*commands);
}
