/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 17:52:47 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/26 06:34:43 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_simbol(int n)
{
	if (n < 0)
		return (-1);
	return (1);
}

static int	get_len(long n, int simbol)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	if (simbol < 0)
		len++;
	return (len);
}

static long	raise_operator(int len, int length_conditional)
{
	int	n;

	n = 1;
	while (--len > length_conditional)
		n *= 10;
	return (n);
}

// Length conditional depends on the simbol
// If there's negative simbol, the length has an extra space
static char	*num_to_str(long num, int len, char *charnum, int simbol)
{
	long	operator;
	int		idx;
	int		length_conditional;

	length_conditional = 0;
	if (simbol < 0)
		length_conditional = 1;
	operator = raise_operator(len, length_conditional);
	idx = 0;
	if (simbol < 0)
	{
		*charnum++ = '-';
		idx++;
	}
	while (len-- > length_conditional)
	{
		*charnum++ = (num / operator) + '0';
		num %= operator;
		operator /= 10;
		idx++;
	}
	return (charnum - idx);
}

char	*ft_itoa(int n)
{
	int		simbol;
	int		len;
	long	positive_n;
	char	*out;

	if (n == 0)
	{
		out = ft_strdup("0");
		return (out);
	}
	positive_n = n;
	simbol = get_simbol(n);
	positive_n *= simbol;
	len = get_len(positive_n, simbol);
	out = ft_calloc(len + 1, sizeof(char));
	if (!out)
		return (NULL);
	num_to_str(positive_n, len, out, simbol);
	return (out);
}

/* int	main(void) */
/* { */
/* 	/1* printf("charnum: %s\n", ft_itoa(8124)); *1/ */
/* 	/1* printf("charnum: %s\n", ft_itoa(543000)); *1/ */
/* 	printf("charnum: %s\n", ft_itoa(0)); */
/* 	/1* printf("charnum: %s\n", ft_itoa(-2147483648)); *1/ */
/* 	return (0); */
/* } */
