/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:36:09 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/19 19:36:03 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;
	int		lexicographic_return;

	if (!s1 && s2)
		return (*s2);
	if (!s2 && s1)
		return (*s1);
	idx = -1;
	if (!n)
		return (0);
	while (++idx < n - 1 && s1[idx] == s2[idx] && s1[idx])
		;
	lexicographic_return = ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
	return (lexicographic_return);
}