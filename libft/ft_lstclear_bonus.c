/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:52:42 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:52:44 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
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

// 	//delete all node
// 	ft_lstclear(&original, free);

// 	//pointer is null
// 	printf("delete all: ");
// 	printf("%p\n", original);	
// }