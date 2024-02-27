/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 02:25:23 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/27 23:52:30 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_content(char c, va_list *argp)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_printchar(va_arg(*argp, int));
	else if ((c == 'd') || (c == 'i'))
		count += ft_printnbr((long)va_arg(*argp, int), 10, HEXL);
	else if (c == 'u')
		count += ft_printnbr((long)va_arg(*argp, unsigned int), 10, HEXL);
	else if (c == 'x')
		count += ft_printnbr((long)va_arg(*argp, unsigned int), 16, HEXL);
	else if (c == 'X')
		count += ft_printnbr((long)va_arg(*argp, unsigned int), 16, HEXU);
	else if (c == 's')
		count += ft_printstr(va_arg(*argp, void *));
	else if (c == 'p')
		count += ft_print_addr((unsigned long)va_arg(*argp, void *), 16, HEXL);
	else
		count += ft_printchar(c);
	return (count);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	argp;
	int		count;

	va_start(argp, fmt);
	count = 0;
	while (*fmt)
	{
		if (*fmt == '%')
			count += print_content(*(++fmt), &argp);
		else
			count += write(FD_STDOUT, fmt, 1);
		++fmt;
	}
	va_end(argp);
	return (count);
}
