/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:23:43 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/02 20:35:52 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
bool check_numeric(char *cmd)
{
	int i;
	i = -1;
	if(cmd[0] == '\0')
		return (true);
	while (cmd[++i])
	{
		if (!ft_isdigit(cmd[i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (false);
		}
	}
	return (true);
}
bool check_two_args(char **cmd)
{
	int i;
	i = -1;
	while (cmd[++i])
		;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (false);
	}
	return (true);
}

int	exit_shell(t_shell *shell , char **cmd)
{
	printf("exit\n");
	if (check_two_args(cmd))
		if(check_numeric(cmd[1]))
			global_status = ft_atoi(cmd[1]);
	
	ft_putstr_fd("exit\n", 1);
	printf("exit status: %d\n", global_status);
	free_shell(shell);
	exit(global_status);
}