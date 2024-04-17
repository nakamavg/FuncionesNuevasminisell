/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:51:32 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/18 01:09:46 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_my_env *env_list)
{
	t_my_env	*tmp;
	t_my_env	*tmp2;

	tmp = env_list;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->name);
		if (*(tmp->value))
			free(tmp->value);
		if (tmp != NULL)
			free(tmp);
		tmp = tmp2;
	}
}

void	free_array_of_strings(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

void	free_env(t_shell *shell)
{
	free(shell->user);
	free(shell->env);
	free(shell->home);
	free(shell->path);
	free(shell->prompt);
	free(shell->input);
}

void	free_shell(t_shell *shell)
{
	free_list(shell->env_list);
	free_array_of_strings(shell->my_env);
	free_env(shell);
	if (!shell->input)
		return ;
	cleanup_cmd_list(&shell->parsed_input);
}
