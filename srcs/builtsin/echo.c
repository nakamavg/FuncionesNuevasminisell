/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:39:17 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/18 10:25:45 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
/* char *search_things(t_shell *shell, char *search)
{
	t_my_env *tmp;
	int i;
	tmp = shell->env_list;
	i = -1;
	while(shell->my_env[++i])
	{
		if(ft_strncmp(shell->my_env[i], search, ft_strlen(search)) == 0)
		{
			return( ft_strdup(shell->my_env[i]+ft_strlen(search)+1));
		}
	}
	tmp = shell->env_list;
	return(NULL);
} */

void echo(t_shell *shell)
{
	t_my_env *save;
	//size_t echo_len;
	char **echo;
	save = shell->env_list;
	int i = 1;	
	echo = ft_split(shell->input, ' ');
	if (echo[1])
	{
		while (echo[1])
		{
			if (echo[i][0] == '$')
			{
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