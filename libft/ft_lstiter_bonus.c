/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:52:56 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:52:58 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// void	print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		if (lst->content)
// 			printf("%s", (char *)lst->content);
// 		if (lst->next)
// 			printf(" --> ");
// 		lst = lst->next;
// 	}
// 	printf("\n");
// }

// void	free_list(t_list *lst)
// {
// 	t_list	*temp;

// 	while (lst)
// 	{
// 		temp = lst;
// 		lst = lst->next;
// 		free(temp);
// 	}
// }

// void print_content(void *content)
// {
// 	if (content)
// 		printf("%s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list *original = ft_lstnew(ft_strdup("original"));
// 	t_list *new = ft_lstnew(ft_strdup("new"));
// 	t_list *one_more = ft_lstnew(ft_strdup("one more"));

// 	//adding two nodes
// 	ft_lstadd_front(&original, new);
// 	ft_lstadd_back(&original, one_more);

// 	//printing original
// 	print_list(original);

// 	//f iterate
// 	ft_lstiter(original, print_content);

// 	//clear list
// 	free_list(original);
// }
