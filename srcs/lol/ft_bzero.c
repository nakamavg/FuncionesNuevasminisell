/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>      +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:55:45 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 20:55:58 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_bzero(void *buffer, size_t len)
{
	unsigned char	*p;

	p = buffer;
	while (len--)
		*p++ = 0;
}
