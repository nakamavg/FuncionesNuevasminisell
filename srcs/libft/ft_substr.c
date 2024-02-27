/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:30:26 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/13 20:52:40 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (len == 0 || start >= slen)
	{
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	if (len > slen - start)
		len = slen - start;
	substr = (char *)ft_calloc((len + 1), sizeof(char));
	if (!substr)
		return (NULL);
	ft_memcpy(substr, (void *)(s + start), len);
	substr[len] = '\0';
	return (substr);
}
