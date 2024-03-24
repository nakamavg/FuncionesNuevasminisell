/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:41:13 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/24 20:31:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_shell *shell)
{
	t_my_env *tmp = shell->env_list;
	char *temp;
	temp = ft_strtrim(shell->input, SPLIT_QUOTE);
		if (ft_strlen(temp) == 2)
		{
			if (chdir(shell->home) == -1)
				ft_error(ERR_DIR_NOT_FOUND, shell->home);
			return ;
		}
		temp += 2;
		temp = ft_strtrim(temp, SPLIT_QUOTE);
		if (chdir(temp) == -1)
			ft_error(ERR_DIR_NOT_FOUND, temp);
		while (shell->env_list)
		{
			if (ft_strncmp(shell->env_list->name, "PWD", 3) == 0)
			{
				shell->env_list->value = getcwd(NULL, 0);
				break ;
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = tmp;
}
