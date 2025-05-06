/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:52:05 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:52:06 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		(ft_lstlast(*lst))->next = new;
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

// int	main(void)
// {
// 	t_list *original = ft_lstnew("original");
// 	t_list *one_more = ft_lstnew("one more");
// 	ft_lstadd_back(&original, one_more);
// 	print_list(original);
// 	free_list(original);
// }