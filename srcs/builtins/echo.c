/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:39:17 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/23 17:34:23 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_names(char *name, char *search)
{
	if (!name || !search)
		return (0);
	if (ft_strlen(search) == ft_strlen(name))
		if (ft_strncmp(name, search, ft_strlen(search)) == 0)
			return (1);
	return (0);
}

char	*search_echo(t_shell *shell, char *search)
{
	t_my_env	*tmp;

	tmp = shell->env_list;
	while (tmp)
	{
		if (check_names(tmp->name, search))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	tmp = shell->env_list;
	return (NULL);
}

static void	print_escaped_characters(char *str)
{
	int	idx;
	int	len;

	len = ft_strlen(str);
	idx = 0;
	while (str[idx] && idx < len)
	{
		printf("%c", str[idx]);
		idx++;
	}
}

void	echo(char **cmd)
{
	int	idx;
	int	lnbr;

	idx = 1;
	lnbr = 1;
	if (cmd[idx] && check_names(cmd[idx], "-n"))
	{
		lnbr = 0;
		idx++;
	}
	while (cmd[idx] && check_names(cmd[idx], "-n"))
		idx++;
	while (cmd[idx] && cmd[idx])
	{
		print_escaped_characters(cmd[idx]);
		if (cmd[idx + 1])
			printf(" ");
		idx++;
	}
	if (!lnbr)
		printf("%%");
	else
		printf("\n");
}
