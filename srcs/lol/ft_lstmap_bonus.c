/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:42:39 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/15 08:13:37 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// I need to use lst clear, because if one node fails allocation,
// we return the function without the new list (this means, remove
// the already allocated content)
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	void	*mapd_content;

	if (!lst)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		mapd_content = f(lst->content);
		node = ft_lstnew(mapd_content);
		if (!node)
		{
			if (mapd_content)
				free(mapd_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		lst = lst->next;
	}
	return (new_list);
}

// void	del(void * inp)
// {
// 	printf("address removed: %p\n", inp);
// }
//
// void *f(void * inp)
// {
// 	return inp;
// }
//
// int main()
// {
//     t_list *list = NULL;
//
//     // Test ft_lstnew
//     t_list *node1 = ft_lstnew("Node 1 Content");
//     t_list *node2 = ft_lstnew("Node 2 Content");
//     t_list *node3 = ft_lstnew("Node 3 Content");
//
//     // Test ft_lstadd_front
//     ft_lstadd_front(&list, node3);
//     ft_lstadd_front(&list, node2);
//     ft_lstadd_front(&list, node1);
// 	// ft_lstmap(list, f, del);
//
//     // Add more tests for your other functions
// 	// ft_lstadd_back(&list, node3);
// 	// ft_lstclear(&list, del);
//     // Print the linked list
//     // printf("Linked List Content:\n");
//     // t_list *current = list;
//     // while (current != NULL)
//     // {
//     //     printf("%s\n", (char *)current->content);
//     //     printf("%p\n", current);
//     //     current = current->next;
//     // }
// 	t_list *new = ft_lstmap(list, f, del);
//     printf("NEW linked List Content:\n");
//     while (new != NULL)
//     {
//         printf("%s\n", (char *)new->content);
//         printf("%p\n", new);
//         new = new->next;
//     }
//
//     // Don't forget to free the allocated memory when done
//     // (you should have a function for freeing the list nodes)
//
//     return 0;
// }
