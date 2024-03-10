/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:12:09 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/10 12:13:06 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*  void check_input(t_shell *shell)
{
	int i;

	i = 0;
	while(shell->input[i])
	{
		if(shell->input[i] == "$" && shell->input[i+1])
			initiate_export(shell, i);	 
	}
}

void initiate_export(t_shell *shell, int i)
{
	while(shell->input[i])
	{
		if(shell->input[i] == " ")
			break;
		if (shell->input[i] == "=")
		{
		}
		
		i++;
	}
}  */
void get_things(t_shell *shell)
{
	shell->user = getenv("USER");
	shell->env = getenv("PATH");
	shell->home = getenv("HOME");
	shell->prompt = ft_strjoin(shell->user, " minishell$ ");
}
int ft_strlen_pp(char **container)
{
	int y;
	y = -1;
	while(container[++y])
	;
	return(y);		
}
void ft_getenv(t_shell *shell, char **env)
{
	shell->env_list = NULL;
	int y;
	y = -1;
	shell->my_env = ft_calloc(ft_strlen_pp((env))+1,sizeof(char *));
	if(!shell->my_env)
		return ;
	while(env[++y])
		shell->my_env[y] = ft_strdup(env[y]);
}
