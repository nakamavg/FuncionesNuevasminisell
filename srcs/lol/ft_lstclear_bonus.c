/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:34 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/13 15:41:36 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		curr = *lst;
		*lst = curr->next;
		ft_lstdelone(curr, del);
	}
}

// void	del(void * inp)
// {
// 	printf("address removed: %p\n", inp);
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
//     ft_lstadd_front(&list, node2);
//     ft_lstadd_front(&list, node1);
//
//     // Add more tests for your other functions
// 	ft_lstadd_back(&list, node3);
// 	ft_lstclear(&list, del);
//     // Print the linked list
//     printf("Linked List Content:\n");
//     t_list *current = list;
//     while (current != NULL)
//     {
//         printf("%s\n", (char *)current->content);
//         printf("%p\n", current);
//         current = current->next;
//     }
//
//     // Don't forget to free the allocated memory when done
//     // (you should have a function for freeing the list nodes)
//
//     return 0;
// }
