/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:17:07 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:17:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	len_s1;
	size_t	len_s2;
	char	*output;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total_len = len_s1 + len_s2 + 1;
	output = (char *)ft_calloc(total_len, sizeof(char));
	if (output == NULL)
		return (NULL);
	ft_memcpy(output, (char *)s1, len_s1);
	ft_memcpy(output + len_s1, (char *)s2, len_s2);
	return (output);
}
