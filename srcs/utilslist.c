/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilslist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 01:42:16 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/10 19:47:00 by dgomez-m         ###   ########.fr       */
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

void	add_env(t_my_env **env, t_my_env *new)
{
	t_my_env	*tmp;

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

void	delone_env(t_my_env *delete)
{
	t_my_env	*pre;
	t_my_env	*next;

	pre = delete->prev;
	next = delete->next;
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
	free(delete->name);
	if (*delete->value)
		free(delete->value);
	free(delete);
	delete = NULL;
}

void	add_env_back(t_my_env **env, t_my_env *new)
{
	t_my_env	*tmp;

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
