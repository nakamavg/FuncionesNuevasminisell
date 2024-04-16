/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:41:18 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/16 16:42:06 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_quote(int *s_quote, int *d_quote, char c)
{
	*s_quote = handle_quote(c, *s_quote, d_quote, '\'');
	*d_quote = handle_quote(c, *d_quote, s_quote, '"');
}

int	handle_quote(char c, int quote, int *compare, int type)
{
	if (c == type && !quote)
	{
		if (*compare)
			*compare += 1;
		return (1);
	}
	else if (c == type && quote)
		return (0);
	return (quote);
}
