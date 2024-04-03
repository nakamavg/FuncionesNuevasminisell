/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:23:43 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/03 13:50:39 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool check_numeric(char *cmd)
// {
// 	int i;
// 	i = -1;
// 	if(cmd[0] == '\0')
// 		return (true);
// 	while (cmd[++i])
// 	{
// 		if (!ft_isdigit(cmd[i]))
// 		{
// 			ft_putstr_fd("exit: ", 2);
// 			ft_putstr_fd(cmd, 2);
// 			ft_putstr_fd(": numeric argument required\n", 2);
// 			return (false);
// 		}
// 	}
// 	return (true);
// }
// bool check_two_args(char **cmd)
// {
// 	int i;
// 	i = -1;
// 	while (cmd[++i])
// 		;
// 	if (i > 2)
// 	{
// 		ft_putstr_fd("exit: too many arguments\n", 2);
// 		return (false);
// 	}
// 	return (true);
// }

int	check_number_of_args(char **cmd)
{
	int	idx;

	idx = -1;
	while (cmd[++idx])
		;
	return (idx);
}

int	exit_shell(t_shell *shell , char **cmd)
{
	int	number_of_args;

	number_of_args = check_number_of_args(cmd);
	if (number_of_args > 2)
	{
		global_status = 1;	
		return (printf("exit: too many arguments\n"), global_status);
	}
	else if (number_of_args == 2)
		global_status = ft_atoi(cmd[1]);
	else
		global_status = 0;
	free_shell(shell);
	exit(global_status);
}