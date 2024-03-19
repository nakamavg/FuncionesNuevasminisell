/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:39:17 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/19 18:07:29 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"
int check_names(char *name, char *search)
{
	if(ft_strlen(search) == ft_strlen(name))
		if(ft_strncmp(name, search, ft_strlen(search)) == 0)
			return(1);
	return(0);
}
char *search_echo(t_shell *shell, char *search)
{
	t_my_env *tmp;
	int i;
	tmp = shell->env_list;
	i = -1;
	while(shell->my_env[++i])
	{
		
		if(check_names(shell->my_env[i], search) == 1)
		{
			return( ft_strdup(shell->my_env[i]+ft_strlen(search)+1));
		}
	}
	tmp = shell->env_list;
	return(NULL);
}

void echo(t_shell *shell)
{
	t_my_env *save;
	//size_t echo_len;
	char **echo;
	save = shell->env_list;
	echo = ft_split(shell->input, ' ');
	if (echo[1])
	{
		if (echo[1][0] == '$')
		{
			char *tmp;
			tmp = search_echo(shell, &echo[1][1]);
			if (tmp)
			{
				ft_putstr_fd(tmp, STDOUT_FILENO);
				free(tmp);
			}
		}
		else
		{
			ft_putstr_fd(echo[1], STDOUT_FILENO);
		}
		printf("\n");
	}
	else
		printf("\n");
	shell->env_list = save;
}