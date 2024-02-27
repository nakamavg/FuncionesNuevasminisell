/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:36:09 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:39:00 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	idx;
	int		lexicographic_return;

	idx = -1;
	if (!n)
		return (0);
	while (++idx < n - 1 && s1[idx] == s2[idx] && s1[idx])
		;
	lexicographic_return = ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
	return (lexicographic_return);
}
