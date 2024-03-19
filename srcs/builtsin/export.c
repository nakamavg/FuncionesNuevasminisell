/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:45 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/19 14:03:18 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_input(char *input)
{
	int i;
	i = -1;
	while(input[++i])
	{
		if(input[i] == ' ')
			return (1);
	}
	return (0);
}
bool check_if_exist(t_shell *env, char *name, char *value)
{
	t_my_env *tmp;
	tmp = env->env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
		{
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
void equal_handler(t_shell *shell, char *name, char *value)
{
	if(check_if_exist(shell, name, value))
		return ;
	add_env(&shell->env_list, ft_envnew(name, value, shell->env_list));

}

void 	realloc_env(t_shell *shell, char *newvar)
{
	t_my_env *save_env;
	char **tmp;
	
	save_env = shell->env_list;
	newvar +=7;
	newvar=ft_strtrim(newvar, SPLIT_QUOTE);
		if(check_input(newvar) == 1)
				ft_error(ERR_SPACES_IN_VAR,&newvar[0]);
	if(ft_isalpha(newvar[0]) == 0 && newvar[0] != 95)
	{
		if(ft_isdigit(newvar[0]))
			return (ft_error(ERR_INVALID_CHAR,&newvar[0]));
		else
			return (ft_error(ERR_INVALID_CTXT,&newvar[0]));
			
	}
	tmp = ft_split(newvar, '=');
	if(ft_strlen_pp(tmp) == 2)
		equal_handler(shell, tmp[0], tmp[1]);
	else
		equal_handler(shell, tmp[0], ft_strdup("''"));
	free(tmp);
	shell->env_list = save_env;
}
void export(t_shell *shell)
{
	int idx;
	idx = 5;
	char *temp;
	temp = ft_strtrim(shell->input, SPLIT_QUOTE);
	if (ft_strncmp(temp,"export", ft_strlen(temp))== 0)
		return(	print_env(shell->env_list));
	else
		return(realloc_env(shell, temp));

}


