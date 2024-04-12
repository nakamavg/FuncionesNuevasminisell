/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_variable_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:54:33 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/12 13:08:01 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	search_token(char *cmd, int idx, int jdx)
{
	if (ft_isspace(cmd[idx + jdx]) || cmd[idx + jdx] == '"' || cmd[idx
			+ jdx] == '\'' || cmd[idx + jdx] == '=')
	{
		return (false);
	}
	return (true);
}
