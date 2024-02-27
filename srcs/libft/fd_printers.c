/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_printers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:53:09 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/28 00:05:05 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fd_printchar(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_fd_print_addr(int fd, unsigned long nbr, int base, char *nbr_formatter)
{
	int		count;
	int		idx;
	char	buffer[MAX_LONG_LEN];

	count = ft_fd_printstr(fd, "0x");
	idx = 0;
	if (nbr == 0)
		return (count += ft_fd_printchar(fd, '0'));
	while (nbr > 0)
	{
		buffer[idx++] = nbr_formatter[nbr % base];
		nbr /= base;
	}
	while (idx--)
		count += ft_fd_printchar(fd, buffer[idx]);
	return (count);
}

int	ft_fd_printnbr(int fd, long nbr, int base, char *nbr_formatter)
{
	int		count;
	int		idx;
	char	buffer[MAX_INT_LEN];

	count = 0;
	idx = 0;
	if (nbr < 0)
	{
		count += ft_fd_printchar(fd, '-');
		nbr = -nbr;
	}
	if (nbr == 0)
		return (ft_fd_printchar(fd, '0'));
	while (nbr > 0)
	{
		buffer[idx++] = nbr_formatter[nbr % base];
		nbr /= base;
	}
	while (idx--)
		count += ft_fd_printchar(fd, buffer[idx]);
	return (count);
}

int	ft_fd_printstr(int fd, char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s)
		count += ft_fd_printchar(fd, *s++);
	return (count);
}
