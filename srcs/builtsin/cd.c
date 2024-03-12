/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:41:13 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/12 07:31:59 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void cd (t_shell *shell)
{
	t_my_env *tmp = shell->env_list;
	char *temp;
	temp = ft_strtrim(shell->input, SPLIT_QUOTE);
	if (ft_strncmp(temp,"cd", 2) == 0)
	{
		temp += 2;
		temp = ft_strtrim(temp, SPLIT_QUOTE);
		if (chdir(temp) == -1)
			ft_error(ERR_DIR_NOT_FOUND, temp);
		while(shell->env_list)
		{
			if(ft_strncmp(shell->env_list->name, "PWD", 3) == 0)
			{
				shell->env_list->value = getcwd(NULL, 0);
				break;
			}
			shell->env_list = shell->env_list->next;
		}
		shell->env_list = tmp;
	}
}