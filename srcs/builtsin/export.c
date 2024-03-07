/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:45 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/07 17:55:48 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void realloc_env(t_shell *shell, char *newvar)
{
	int y;
	y = -1;
	char **tmp;
	tmp= ft_calloc(ft_strlen_pp(shell->my_env)+2,sizeof(char *));
	while(shell->my_env[++y])
	{
		tmp[y] = ft_strdup(shell->my_env[y]);
		free(shell->my_env[y]);
	}
	printf("la nueva data es : %s\n", newvar);
	free(shell->my_env);
	tmp[y]=ft_strdup(newvar);
	shell->my_env = tmp;
	shell->my_env[y + 1] = NULL;
}
void export(t_shell *shell)
{
// export nos agrega variables de entorno para $variableentorno
//o  nos la cambia
int idx;
idx = 5;//idx = 6 porque export tiene 6 letras
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


