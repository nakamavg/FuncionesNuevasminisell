/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:45 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/18 04:28:36 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_if_exist(t_shell *env, char *name, char *value)
{
	t_my_env	*tmp;

	tmp = env->env_list;
	while (tmp)
	{
		if (check_names(tmp->name, name))
		{
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	equal_handler(t_shell *shell, char *name, char *value)
{
	if (check_if_exist(shell, name, value))
		return (free(name));
	add_env(&shell->env_list, ft_envnew(name, value, shell->env_list));
	sort_env(shell->env_sys_end);
}

void	realloc_env(t_shell *shell, char **newvar, bool *error_handler)
{
	int		i;
	char	*split[2];
	bool	local_error;

	local_error = false;
	i = 0;
	while (newvar[++i])
	{
		local_error = false;
		if (ft_strchr(newvar[i], '=') == NULL)
		{
			split[0] = ft_strdup(newvar[i]);
			split[1] = ft_strdup(" ");
		}
		else
		{
			split[0] = ft_substr(newvar[i], 0, ft_strchr(newvar[i], '=') - newvar[i]);
			split[1] = ft_substr(ft_strchr(newvar[i], '=') + 1, 0, ft_strlen(ft_strchr(newvar[i], '=') + 1));
		}
		handle_errors_export(split[0], &local_error);
		if (local_error)
		{
			*error_handler = true;
			continue ;
		}
		equal_handler(shell, split[0], split[1]);
	}
}

int	export(t_shell *shell, char **cmd)
{
	bool	error_handler;

	error_handler = false;
	if (!cmd[1])
	{
		print_env(shell->env_list);
		return (0);
	}
	realloc_env(shell, cmd, &error_handler);
	get_things(shell, true);
	return ((int)error_handler);
}
