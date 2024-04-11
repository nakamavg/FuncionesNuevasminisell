/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:41:13 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/11 09:41:12 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_value(t_shell *shell, char *name, char *value)
{
	t_my_env	*tmp;
	t_my_env	*new_entry;

	tmp = shell->env_list;
	while (tmp)
	{
		if (check_names(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	new_entry = malloc(sizeof(t_my_env));
	new_entry->name = ft_strdup(name);
	new_entry->value = ft_strdup(value);
	new_entry->next = shell->env_list;
	shell->env_list = new_entry;
}

void	change_old_pwd(t_shell *shell)
{
	char	*old_pwd;

	old_pwd = search_echo(shell, "PWD");
	insert_value(shell, "OLDPWD", old_pwd);
	free(old_pwd);
}

void	go_direction(char *dir, bool *success)
{
	if (chdir(dir) == -1)
	{
		ft_error(ERR_DIR_NOT_FOUND, dir);
		*success = false;
	}
	else
		*success = true;
}

int	cd(t_shell *shell, char **cmd)
{
	char	**temp;
	char	*new_pwd;
	bool	success;

	temp = ft_split(shell->input, ' ');
	if (!temp[1] || ft_strncmp(temp[1], "~", 1) == 0)
		go_direction(shell->home, &success);
	else
		go_direction(cmd[1], &success);
	if (!success)
	{
		free_array_of_strings(temp);
		return (1);
	}
	change_old_pwd(shell);
	new_pwd = getcwd(NULL, 0);
	insert_value(shell, "PWD", new_pwd);
	free(new_pwd);
	free_array_of_strings(temp);
	return (0);
}
