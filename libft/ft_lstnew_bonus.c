/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:51:10 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:51:12 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
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
// 	t_list	*new;

// 	new = ft_lstnew("123");
// 	print_list(new);
// 	free_list(new);
// }