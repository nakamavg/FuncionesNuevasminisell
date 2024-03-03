/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:55:16 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/09 17:11:04 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		operator;
	long	output;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	operator = 1;
	if (*str == '-')
	{
		operator *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	output = 0;
	while (ft_isdigit(*str))
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (output * operator);
}
