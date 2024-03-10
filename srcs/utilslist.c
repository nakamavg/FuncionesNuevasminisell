/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:42:16 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/10 06:35:43 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// inicializa la lista de variables de entorno
t_my_env	*ft_envnew(void *name, void *value)
{
	t_my_env	*new_l;
	new_l = malloc(sizeof(struct s_my_env));
	if (!new_l)
		return (NULL);
	new_l->name = name;
	new_l->value = value;
	new_l->next = NULL;
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
}
void delone_env(t_my_env **env, char *name)
{
	t_my_env *tmp;
	t_my_env *prev;
	tmp = *env;
	if (tmp && ft_strcmp(tmp->name, name) == 0)
	{
		*env = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp && ft_strcmp(tmp->name, name) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	prev->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
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
