/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:41:13 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:53 by dgomez-m         ###   ########.fr       */
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

void	go_direction(char *dir)
{
	if (chdir(dir) == -1)
		ft_error(ERR_DIR_NOT_FOUND, dir);
}

void	cd(t_shell *shell)
{
	char	**temp;
	char	*new_pwd;

	temp = ft_split(shell->input, ' ');
	if (!temp[1] || ft_strncmp(temp[1], "~", 1) == 0)
		go_direction(shell->home);
	else
		go_direction(temp[1]);
	change_old_pwd(shell);
	new_pwd = getcwd(NULL, 0);
	insert_value(shell, "PWD", new_pwd);
	free(new_pwd);
	free(temp);
}
