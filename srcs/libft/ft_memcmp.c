/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:11:45 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:11:47 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a;
	const unsigned char	*b;

	if (!n)
		return (0);
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (--n)
	{
		if (*a != *b)
			break ;
		a++;
		b++;
	}
	return (*a - *b);
}
