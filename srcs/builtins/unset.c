/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:33:50 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/23 18:05:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_value(t_shell *shell, char *name)
{
	t_my_env	*tmp;
	t_my_env	*next;

	tmp = shell->env_list;
	while (tmp)
	{
		if (check_names(tmp->name, name))
		{
			next = tmp->next;
			if (tmp == shell->env_list)
				shell->env_list = next;
			delone_env(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}

void	unset(t_shell *shell, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		unset_value(shell, cmd[i]);
	}
	get_things(shell, true);
}
