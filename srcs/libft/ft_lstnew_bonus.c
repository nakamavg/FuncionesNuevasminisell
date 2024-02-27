/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:42:55 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/13 15:42:56 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_l;

	new_l = malloc(sizeof(struct s_list));
	if (!new_l)
		return (NULL);
	new_l->content = content;
	new_l->next = NULL;
	return (new_l);
}
