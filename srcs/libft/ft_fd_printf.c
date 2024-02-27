/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:49:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/28 00:09:31 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fd_print_content(int fd, char c, va_list *argp)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_fd_printchar(fd, va_arg(*argp, int));
	else if ((c == 'd') || (c == 'i'))
		count += ft_fd_printnbr(fd, (long)va_arg(*argp, int), 10, HEXL);
	else if (c == 'u')
		count += ft_fd_printnbr(fd, (long)va_arg(*argp, unsigned int),
				10, HEXL);
	else if (c == 'x')
		count += ft_fd_printnbr(fd, (long)va_arg(*argp, unsigned int),
				16, HEXL);
	else if (c == 'X')
		count += ft_fd_printnbr(fd, (long)va_arg(*argp, unsigned int),
				16, HEXU);
	else if (c == 's')
		count += ft_fd_printstr(fd, va_arg(*argp, void *));
	else if (c == 'p')
		count += ft_fd_print_addr(fd, (unsigned long)va_arg(*argp, void *),
				16, HEXL);
	else
		count += ft_fd_printchar(fd, c);
	return (count);
}

int	ft_fd_printf(int fd, const char *fmt, ...)
{
	va_list	argp;
	int		count;

	va_start(argp, fmt);
	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
			count += fd_print_content(fd, *(++fmt), &argp);
		else
			count += write(fd, fmt, 1);
		++fmt;
	}
	va_end(argp);
	return (count);
}
