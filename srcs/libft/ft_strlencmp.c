/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlencmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:21:11 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/19 16:22:20 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int ft_strlencmp(const char *s1, const char *s2)
{
	int i;

	i = -1;
	while(s1[++i] && s2[i])
	{
		if(s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}

	return (0);
}