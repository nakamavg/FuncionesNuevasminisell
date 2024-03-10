/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:45 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/10 13:08:48 by dgomez-m         ###   ########.fr       */
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

void realloc_env(t_shell *shell, char *newvar)
{
	
	char **tmp;
	newvar +=7;
	newvar=ft_strtrim(newvar, "\t\n\v\f\r ");
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
	if (!tmp)
		return ;
	add_env(&shell->env_list, ft_envnew(tmp[0], tmp[1], shell->env_list));
	
	
}
void export(t_shell *shell)
{
int idx;
idx = 5;
char *temp;
temp = ft_strtrim(shell->input, "\t\n\v\f\r ");
if (ft_strncmp(temp,"export", ft_strlen(temp))== 0)
	return(	print_env(shell->env_list));

if(ft_strchr(temp,'=')!= NULL)
	realloc_env(shell, temp);
}


