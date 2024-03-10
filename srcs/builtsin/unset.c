/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:33:50 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/10 04:43:05 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* static int check_input(char *input)
{
	int i;
	i = -1;
	while(input[++i])
	{
		if(input[i] == ' ')
			return (1);
	}
	return (0);
} */

/* static void realloc_env(t_shell *shell, char *newvar)
{
	printf("shell->my_env: %s\n", shell->my_env[0]);
	printf("newvar:%s\n", newvar);
	while(newvar)
}	 */

/* void unset(t_shell *shell)
{
int idx;
idx = 5;
char *temp;
temp = ft_strtrim(shell->input, "\t\n\v\f\r ");
if (ft_strncmp(temp,"unset", ft_strlen(temp))== 0)
	{
		if(ft_strlen(temp) == 5)
			return (ft_error(UNSET_NOT_ARG, "unset"));
		else if(ft_strchr(temp,'=')!= NULL)
			return (ft_error(ERR_INVALID_CTXT, temp));
	}
temp += 5;
	realloc_env(shell, temp);
} */

 