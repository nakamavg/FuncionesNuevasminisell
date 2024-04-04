/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:58:24 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/04 02:47:48 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool auxiliar_errors_export(char input)
{
	if (input == ' ')
		return (1);
	if ((!ft_isdigit(input) && !ft_isalnum(input) && input != '_'))
		return (1);

	return (0);
}

void handle_errors_export(char *input , bool *local_error)
{
	int i;
	i = -1;
	if (ft_isdigit(input[0]))
	{
		*local_error = true;
		ft_error(ERR_INVALID_CHAR, input);
	}
	else
	{
		while(input[++i])
		{
			if(auxiliar_errors_export(input[i]))
			{
				*local_error = true;
				ft_error(ERR_INVALID_CHAR, input);
				break;
			}
		}
	}
}
