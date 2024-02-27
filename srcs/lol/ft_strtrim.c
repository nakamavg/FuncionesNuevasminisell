/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:21:40 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:29:54 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*output;

	start = 0;
	if (!s1)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start == ft_strlen(s1))
	{
		output = (char *)ft_calloc(1, sizeof(char));
		if (!output)
			return (NULL);
		return (output);
	}
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	output = ft_substr(s1, start, (end - start) + 1);
	return (output);
}
