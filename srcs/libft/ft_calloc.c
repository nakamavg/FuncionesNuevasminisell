/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:57:54 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 23:47:51 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*allocated;

	total = count * size;
	allocated = malloc(total);
	if (allocated == NULL)
		return (NULL);
	ft_memset(allocated, 0, total);
	return (allocated);
}
