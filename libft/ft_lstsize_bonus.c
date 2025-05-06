/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:51:39 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:51:40 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
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
// 	t_list *new = ft_lstnew("new");
// 	t_list *one_more = ft_lstnew("one more");
// 	ft_lstadd_front(&original, new);
// 	print_list(original);
// 	printf("%d\n", ft_lstsize(original));
// 	ft_lstadd_front(&original, one_more);
// 	print_list(original);
// 	printf("%d\n", ft_lstsize(original));
// 	free_list(original);
// }