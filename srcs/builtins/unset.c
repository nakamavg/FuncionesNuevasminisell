/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:33:50 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/25 16:48:28 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unset (t_shell *shell)
{
	// int i;
	// i = 5;
	t_my_env *tmp = shell->env_list;
	char *temp;
	temp = ft_strtrim(shell->input, SPLIT_QUOTE);
	if (ft_strncmp(temp,"unset", ft_strlen(temp))== 0)
		return(ft_error(UNSET_NOT_ARG, NULL));
	temp += 5;
	temp = ft_strtrim(temp, SPLIT_QUOTE);
	while(shell->env_list)
	{
		if(ft_strncmp(shell->env_list->name, temp, ft_strlen(temp)) == 0)
		{
			delone_env(shell);
			
			break;
		}
		shell->env_list = shell->env_list->next;
	}
	shell->env_list = tmp;
}

 