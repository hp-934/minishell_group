/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:52:22 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:52:25 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

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

// void	delete(void *content)
// {
// 	free(content);
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
// 	printf("previously: ");
// 	print_list(original);

// 	//saving next node
// 	t_list *whats_left = original->next;

// 	//delete first node
// 	ft_lstdelone(original, delete);

// 	//printing what's left
// 	printf("delete one: ");
// 	print_list(whats_left);
// 	free_list(whats_left);
// }