/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:14:24 by alberrod          #+#    #+#             */
/*   Updated: 2023/12/11 21:14:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(int n)
{
	int	len;

	len = 1;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	get_operator(long n)
{
	int	operator;

	operator = 1;
	while (n > 9)
	{
		n /= 10;
		operator *= 10;
	}
	return (operator);
}

static void	write_number(int simbol, long out_n, int operator, int fd)
{
	int		idx;
	int		len;
	char	to_print;

	len = get_length(operator);
	idx = 0;
	if (simbol < 0)
	{
		write(fd, "-", 1);
	}
	while (idx < len - 1)
	{
		to_print = (out_n / operator) + '0';
		write(fd, &to_print, 1);
		out_n %= operator;
		operator /= 10;
		idx++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		operator;
	long	simbol;
	long	out_n;

	if (n < 0)
		simbol = -1;
	else
		simbol = 1;
	out_n = n * simbol;
	operator = get_operator(out_n);
	write_number(simbol, out_n, operator, fd);
}
