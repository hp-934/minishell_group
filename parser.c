/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/08 17:51:34 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_NONE 0
#define ERROR_QUOTE 1


volatile int	g_signal = 0;

int	check_quotes(char *str)
{
	int	count_single;
	int	count_double;

	count_single = 0;
	count_double = 0;
	while (*str)
	{
		if (*str == '\'')
			count_single++;
		else if (*str == '"')
			count_double++;
		str++;
	}
	if (count_single % 2 == 1 || count_double % 2 == 1)
		return (ERROR_QUOTE);
	return (ERROR_NONE);
}

// t_list *parser(char *str)
// {
// 	t_list	*parsed_prompt;

// 	if (check_quotes(str) != ERROR_NONE)
// 		return (NULL);
// 	parsed_prompt = ft_lstnew(str);
// 	return (parsed_prompt);
// }

void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}

int	main(void)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	signal(SIGQUIT, handle_sigquit);
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break;
		while (check_quotes(str ) != ERROR_NONE)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			tmp1 = ft_strjoin(str, "\n");
			free(str);
			tmp2 = readline(">");
			str = ft_strjoin(tmp1, tmp2);
			free(tmp1);
			free(tmp2);
		}
		add_history(str);
		free(str);
	}
	rl_clear_history();
	return (0);
}