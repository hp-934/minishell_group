/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:53:09 by hogu              #+#    #+#             */
/*   Updated: 2024/10/04 16:53:10 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		node = ft_lstnew(new_content);
		if (!node)
		{
			if (new_content)
				del(new_content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, node);
		lst = lst->next;
	}
	return (result);
}

// char	toupper_adapter(unsigned int i, char c)
// {
// 	(void) i;
// 	return (char)ft_toupper((int)c);
// }

// void	*to_upper(void *content)
// {
// 	char *new_str;

// 	new_str = ft_strmapi((char *)content, toupper_adapter);
// 	return new_str;
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
// 	t_list *original = ft_lstnew(ft_strdup("original"));
// 	t_list *new = ft_lstnew(ft_strdup("new"));
// 	ft_lstadd_front(&original, new);

// 	//printing original
// 	printf("Original list: ");
// 	print_list(original);

// 	//printing mapped list
// 	t_list *mapped = ft_lstmap(original, to_upper, free);
// 	printf("Mapped list: ");
// 	print_list(mapped);

// 	//clear list
// 	ft_lstclear(&original, free);
// 	ft_lstclear(&mapped, free);
// }