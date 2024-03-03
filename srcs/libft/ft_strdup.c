/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:16:24 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:16:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	int		len;
	char	*out;

	len = ft_strlen(str1) + 1;
	out = ft_calloc(len, sizeof(char));
	if (out == NULL)
		return (NULL);
	ft_memcpy(out, (char *)str1, len);
	return (out);
}
