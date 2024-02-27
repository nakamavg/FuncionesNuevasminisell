/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:17:59 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/15 07:59:13 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;
	size_t	ret;

	idx = -1;
	while (++idx < dstsize && *dst)
		dst++;
	ret = ft_strlcpy(dst, src, dstsize - idx);
	return (ret + idx);
}
