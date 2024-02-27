/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 02:26:32 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/27 23:56:13 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	return (write(FD_STDOUT, &c, 1));
}

int	ft_print_addr(unsigned long nbr, int base, char *nbr_formatter)
{
	int		count;
	int		idx;
	char	buffer[MAX_LONG_LEN];

	count = ft_printstr("0x");
	idx = 0;
	if (nbr == 0)
		return (count += ft_printchar('0'));
	while (nbr > 0)
	{
		buffer[idx++] = nbr_formatter[nbr % base];
		nbr /= base;
	}
	while (idx--)
		count += ft_printchar(buffer[idx]);
	return (count);
}

int	ft_printnbr(long nbr, int base, char *nbr_formatter)
{
	int		count;
	int		idx;
	char	buffer[MAX_INT_LEN];

	count = 0;
	idx = 0;
	if (nbr < 0)
	{
		count += ft_printchar('-');
		nbr = -nbr;
	}
	if (nbr == 0)
		return (ft_printchar('0'));
	while (nbr > 0)
	{
		buffer[idx++] = nbr_formatter[nbr % base];
		nbr /= base;
	}
	while (idx--)
		count += ft_printchar(buffer[idx]);
	return (count);
}

int	ft_printstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
		count += ft_printchar(*s++);
	return (count);
}
