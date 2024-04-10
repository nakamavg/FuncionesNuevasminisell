/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:23:43 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/10 19:24:34 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_number_of_args(char **cmd)
{
	int	idx;

	idx = -1;
	while (cmd[++idx])
		;
	return (idx);
}

int	exit_shell(t_shell *shell, char **cmd)
{
	int	number_of_args;

	number_of_args = check_number_of_args(cmd);
	if (number_of_args > 2)
	{
		g_status = 1;
		return (printf("exit: too many arguments\n"), g_status);
	}
	else if (number_of_args == 2)
		g_status = ft_atoi(cmd[1]);
	else
		g_status = 0;
	free_shell(shell);
	exit(g_status);
}
