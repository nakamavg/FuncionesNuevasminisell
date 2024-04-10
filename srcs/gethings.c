/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:12:09 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/10 21:36:12 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_things(t_shell *shell, char *search)
{
	t_my_env	*tmp;

	tmp = shell->env_list;
	while (tmp)
	{
		if (check_names(tmp->name, search))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*search_expand(t_shell *shell, char *search)
{
	t_my_env	*node;

	node = shell->env_list;
	while (node)
	{
		if (check_names(node->name, search))
			return (ft_strdup(node->value));
		node = node->next;
	}
	return (NULL);
}

void	get_things(t_shell *shell)
{
	shell->user = search_things(shell, "USER");
	shell->env = search_things(shell, "PWD");
	shell->home = search_things(shell, "HOME");
	shell->path = search_things(shell, "PATH");
	shell->env_sys_end = go_to_end(shell->env_list);
	shell->prompt = ft_sprintf("%s%s%s%s@minishell$%s ", YELLOW, shell->user,
			RESET, PURPLE, RESET);
}

void	ft_getenv(t_shell *shell, char **env)
{
	int	y;

	shell->env_list = NULL;
	y = -1;
	shell->my_env = ft_calloc(ft_strlen_pp((env)) + 1, sizeof(char *));
	if (!shell->my_env)
		return ;
	while (env[++y])
		shell->my_env[y] = ft_strdup(env[y]);
}

void	ft_env_split(t_shell *shell)
{
	int		i;
	int		jdx;
	char	*name;
	char	*value;

	shell->env_list = NULL;
	i = -1;
	while (shell->my_env[++i])
	{
		jdx = -1;
		while (shell->my_env[i][++jdx] != '=')
			;
		name = ft_substr(shell->my_env[i], 0, jdx);
		value = ft_strdup(shell->my_env[i] + jdx + 1);
		add_env(&shell->env_list, ft_envnew(name, value, shell->env_list));
	}
}
