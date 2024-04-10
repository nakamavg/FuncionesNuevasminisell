/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:04:45 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/10 19:25:38 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == ' ')
			return (1);
	}
	return (0);
}

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
		return ;
	add_env(&shell->env_list, ft_envnew(name, value, shell->env_list));
	sort_env(shell->env_sys_end);
}

void	realloc_env(t_shell *shell, char **newvar, bool *error_handler)
{
	int		i;
	char	**split;
	bool	local_error;

	local_error = false;
	i = 0;
	while (newvar[++i])
	{
		local_error = false;
		split = ft_split(newvar[i], '=');
		handle_errors_export(split[0], &local_error);
		if (local_error)
		{
			*error_handler = true;
			free(split);
			continue ;
		}
		if (!split[1])
			equal_handler(shell, split[0], "");
		else
			equal_handler(shell, split[0], split[1]);
		free(split);
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
	return ((int)error_handler);
}
