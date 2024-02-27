/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:12:40 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:12:42 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// memmove it can copy forwars and backwards, while memcpy only works forward
// memmove is safer than memcpy because deals with overlapping buffers
#include "libft.h"

static void	cpy_from_start_to_end(char *dest, const char *src, size_t n)
{
	while (n--)
		*dest++ = *src++;
}

static void	cpy_from_end_to_start(char *dest, const char *src, size_t n)
{
	while (n--)
		dest[n] = src[n];
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*char_dest;
	const char	*char_src;

	char_dest = (char *)dest;
	char_src = (const char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (char_dest < char_src)
		cpy_from_start_to_end(char_dest, char_src, n);
	else
		cpy_from_end_to_start(char_dest, char_src, n);
	return (dest);
}
