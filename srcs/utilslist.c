/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:42:16 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/24 20:28:31 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_my_env	*ft_envnew(void *name, void *value, t_my_env *new_l)
{
	new_l = malloc(sizeof(struct s_my_env));
	if (!new_l)
		return (NULL);
	new_l->name = name;
	new_l->value = value;
	new_l->next = NULL;
	new_l->prev = NULL;
	return (new_l);
	
}
void add_env(t_my_env **env, t_my_env *new)
{
	t_my_env *tmp;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
 void delone_env(t_shell *shell)
{
	t_my_env *pre = shell->env_list->prev;
	t_my_env *next = shell->env_list->next;
	if (pre && !next)
	{
		pre->next = NULL;
	}
	else if (!pre && next)
	{
		next->prev = NULL;
	}
	else if (pre && next)
	{
		pre->next = next;
		next->prev = pre;
	}
	
	free(shell->env_list->name);
	free(shell->env_list->value);
	free(shell->env_list);

} 
void add_env_back(t_my_env **env, t_my_env *new)
{
	t_my_env *tmp;
	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
