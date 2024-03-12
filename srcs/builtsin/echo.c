/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:39:17 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/12 07:47:32 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void echo(t_shell *shell)
{
	t_my_env *save;
	char **echo;
	save = shell->env_list;
	int i = 1;	
	echo = ft_split(shell->input, ' ');
	if (echo[1])
	{
		while (echo[i])
		{
			if(echo[i][0] == '$' && echo[i][1] != 0)
			{
				echo[i]++;
				while(shell->env_list)
				{
					if(ft_strncmp(shell->env_list->name, echo[i], ft_strlen(echo[i])) == 0)
					{
						printf("%s ", shell->env_list->value);
						break;
					}
					shell->env_list = shell->env_list->next;
				}
				shell->env_list = shell->env_list;
			}
			else
			printf("%s ", echo[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("\n");
	shell->env_list = save;
}