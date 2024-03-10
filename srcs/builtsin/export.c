/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:45 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/08 03:47:03 by dgomez-m         ###   ########.fr       */
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
	
	newvar +=7;
	newvar=ft_strtrim(newvar, "\t\n\v\f\r ");
		if(check_input(newvar) == 1)
				ft_error(ERR_SPACES_IN_VAR,&newvar[0]);
	if(ft_isalpha(newvar[0]) == 0 && newvar[0] != 95){
		if(ft_isdigit(newvar[0]))
			return (ft_error(ERR_INVALID_CHAR,&newvar[0]));
		else
			return (ft_error(ERR_INVALID_CTXT,&newvar[0]));
			
	}
	int y;
	y = -1;
	char **tmp;
	tmp= ft_calloc(ft_strlen_pp(shell->my_env)+2,sizeof(char *));
	while(shell->my_env[++y])
	{
		tmp[y] = ft_strdup(shell->my_env[y]);
		free(shell->my_env[y]);
	}
	free(shell->my_env);
	tmp[y]=ft_strdup(newvar);
	shell->my_env = tmp;
	shell->my_env[y + 1] = NULL;
}
void export(t_shell *shell)
{
int idx;
idx = 5;
char *temp;
temp = ft_strtrim(shell->input, "\t\n\v\f\r ");
if (ft_strncmp(temp,"export", ft_strlen(temp))== 0)
{
	while(shell->my_env[++idx])
		printf("%s\n", shell->my_env[idx]);
	return;
}
if(ft_strchr(temp,'=')!= NULL)
	realloc_env(shell, temp);
}


