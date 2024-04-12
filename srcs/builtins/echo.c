/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:39:17 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/12 08:06:20 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_names(char *name, char *search)
{
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
	if (str[0] == '"' || str[0] == '\'')
	{
		idx = 1;
		len--;
	}
	else
		idx = 0;
	while (idx < len)
	{
		if (str[idx] == '\\' && str[idx + 1] != '\0')
		{
			if ((str[idx + 1] == 'n') && (str[0] == '"' || str[0] == '\''))
				printf("\\");
			idx++;
			printf("%c", str[idx]);
		}
		else
			printf("%c", str[idx]);
		idx++;
	}
}

void	echo(char **cmd)
{
	int	idx;
	int	lnbr;

	idx = 0;
	lnbr = 1;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])))
	{
		lnbr = 0;
		idx++;
	}
	while (cmd[++idx])
	{
		print_escaped_characters(cmd[idx]);
		if (cmd[idx + 1])
			printf(" ");
	}
	if (!lnbr)
		printf("%%");
	else
		printf("\n");
}
