/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:21:01 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:21:10 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		idx;
	char	*output;

	output = NULL;
	idx = ft_strlen(str) + 1;
	while (--idx > 0 && str[idx] != (char)c)
		;
	if (str[idx] == (char)c)
		output = (char *)&str[idx];
	return (output);
}
