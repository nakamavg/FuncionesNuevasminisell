/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:12:09 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/18 04:56:29 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *search_things(t_shell *shell, char *search)
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
}

void get_things(t_shell *shell)
{
	shell->user = search_things(shell, "USER");
	shell->env = search_things(shell, "PWD");
	shell->home = search_things(shell, "HOME");
	shell->path = search_things(shell, "PATH");
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

void ft_env_split(t_shell *shell)
{
	int i;
	char **tmp;

	shell->env_list = NULL;
	i = -1;
	while (shell->my_env[++i])
	{
		tmp = ft_split(shell->my_env[i], '=');
		add_env(&shell->env_list, ft_envnew(tmp[0], tmp[1], shell->env_list));
		free(tmp);
	}
}

void print_env(t_my_env *env)
{
	while(env)
	{
		if(env->name && env->value && ft_strlen(env->name) > 0 )
				printf("declare -x %s=%s\n", env->name, env->value);
		env = env->next;
	}

}
	
