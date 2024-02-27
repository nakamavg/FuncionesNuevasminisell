/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:27:50 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/09 21:57:24 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// A ultra-minimalistic version of sprintf
// Currently it's only useful for appending strings and ints
// Pending to improve

static char	*printer(char const *container, va_list *args)
{
	char	*res;

	if (ft_strchr("di", *container))
		res = ft_itoa(va_arg(*args, int));
	if (ft_strchr("xX", *container))
		res = ft_puthexa_str(va_arg(*args, size_t));
	if (*container == 'p')
		res = ft_putaddress_str(va_arg(*args, unsigned long));
	if (*container == 's')
		res = str_or_null(va_arg(*args, char *));
	if (*container == 'c')
	{
		res = malloc(2);
		res[0] = (char)va_arg(*args, int);
		res[1] = '\0';
	}
	if (*container == '%')
		res = strdup("%");
	return (res);
}

static char	*allocate_and_copy(char *old_result, char *tmp, int old_len)
{
	char	*result;

	result = malloc(old_len + strlen(tmp) + 1);
	ft_memcpy(result, old_result, old_len);
	ft_memcpy(result + old_len, tmp, strlen(tmp));
	result[old_len + strlen(tmp)] = '\0';
	free(old_result);
	free(tmp);
	return (result);
}

static char	*handle_percent_case(char const **container, va_list *args,
		char *result)
{
	char	*tmp;
	int		old_len;

	tmp = printer(++(*container), args);
	old_len = strlen(result);
	result = allocate_and_copy(result, tmp, old_len);
	return (result);
}

static char	*handle_normal_case(char const **container, char *result)
{
	char	*tmp;
	int		old_len;

	tmp = malloc(2);
	tmp[0] = **container;
	tmp[1] = '\0';
	old_len = strlen(result);
	result = allocate_and_copy(result, tmp, old_len);
	return (result);
}

char	*ft_sprintf(char const *container, ...)
{
	va_list	args;
	char	*result;

	va_start(args, container);
	result = malloc(sizeof(char));
	*result = '\0';
	while (*container)
	{
		if (*container == '%')
			result = handle_percent_case(&container, &args, result);
		else
			result = handle_normal_case(&container, result);
		container++;
	}
	va_end(args);
	return (result);
}
