/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaepark <yaepark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:54:11 by yaepark           #+#    #+#             */
/*   Updated: 2025/05/09 18:00:11 by yaepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERROR_NONE 0
#define ERROR_QUOTE 1


volatile int	g_signal = 0;

void	handle_sigquit(int sig)
{
	(void) sig;
	g_signal = 1;
}

void	del(void *content)
{
	free(content);
}

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

char	*complete_quotes(char *str)
{
	char	*tmp1;
	char	*tmp2;

	rl_on_new_line();
	rl_replace_line("", 0);
	tmp1 = ft_strjoin(str, "\n");
	free(str);
	tmp2 = readline(">");
	if (!tmp2)
	{
		free(tmp1);
		return (NULL);
	}
	str = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (str);
}

void	free_arrays(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void print_content(void *content)
{
	if (content)
		printf("%s\n", (char *)content);
}

t_list	*tokenize_input(char *str)
{
	t_list	*input;
	t_list	*new;
	char	**split_str;
	int		i;

	split_str = ft_split(str, ' ');
	free(str);
	if (!split_str)
		return(NULL);
	i = 0;
	input = NULL;
	while (split_str[i])
	{
		new = ft_lstnew(strdup(split_str[i]));
		ft_lstadd_back(&input, new);
		i++;
	}
	free_arrays((void **)split_str);
	return (input);
}

t_list	*parser(char *str)
{
	t_list	*input;

	while (check_quotes(str ) != ERROR_NONE)
	{
		str = complete_quotes(str);
		if (!str)
			return (NULL);
	}
	add_history(str);
	input = tokenize_input(str);
	if (!input)
		return (NULL);
	return (input);
}

int	main(void)
{
	char	*str;
	t_list	*input;

	signal(SIGQUIT, handle_sigquit);
	input = NULL;
	while (g_signal == 0)
	{
		str = readline(">");
		if (!str)
			break;
		input = parser(str);
		if (!input)
			break;
		ft_lstiter(input, print_content);
	}
	if (input)
		ft_lstclear(&input, del);
	rl_clear_history();
	return (0);
}