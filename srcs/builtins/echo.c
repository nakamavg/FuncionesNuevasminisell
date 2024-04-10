/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:39:17 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/11 01:43:29 by dgomez-m         ###   ########.fr       */
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

	idx = -1;
	while (str[++idx])
	{
		if (str[idx] == '\\' && str[idx + 1] != '\0')
		{
			if ((str[idx + 1] == 'n') && (str[0] == '"' || str[0] == '\''))
				printf("\\");
			idx++;
			printf("%c", str[idx]);
		}
		else if (str[idx] != '\'' && str[idx] != '"')
			printf("%c", str[idx]);
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

// void echo(t_shell *shell)
// {
// 	t_my_env *save;
// 	//size_t echo_len;
// 	char **echo;
// 	save = shell->env_list;
// 	echo = ft_split(shell->input, ' ');
// 	if (echo[1])
// 	{
// 		if (echo[1][0] == '$')
// 		{
// 			char *tmp;
// 			tmp = search_echo(shell, &echo[1][1]);
// 			if (tmp)
// 			{
// 				ft_putstr_fd(tmp, STDOUT_FILENO);
// 				free(tmp);
// 			}
// 		}
// 		else
// 		{
// 			ft_putstr_fd(echo[1], STDOUT_FILENO);
// 		}
// 		printf("\n");
// 	}
// 	else
// 		printf("\n");
// 	shell->env_list = save;
// }