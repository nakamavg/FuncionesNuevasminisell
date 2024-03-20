/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:22:03 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 17:22:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_the_variable(char *cmd)
{
	int idx = 0;
	int jdx;
	char *variable;
	char *begin;
	char *end;
	char *out;

	while (cmd[idx])
	{
		if (cmd[idx] == '$')
		{
			begin = ft_substr(cmd, 0, idx);
			jdx = 0;
			while (cmd[idx + jdx] && !ft_isspace(cmd[idx + jdx] && cmd[idx + jdx] != '\"'))
				jdx++;
			variable = ft_substr(cmd, idx + 1, jdx - 1);
			end = ft_substr(cmd, idx + jdx, ft_strlen(cmd) - idx - jdx);
		}
		idx++;
	}
	// TODO: USE OUR OWN VERSION OF GETENV
	// out = ft_sprintf("%s%s%s", begin, getenv(variable), end);
	printf("variable: %s\n", variable);
	out = ft_sprintf("%s%s%s", begin, "HERE GOES A VARIABLE", end);
	free(begin);
	free(variable);
	free(end);
	return (out);
}

char	**expand_variable(char **cmd)
{
	int idx = -1;
	int jdx;
	char *tmp;
	int quote;

	quote = 0;
	while (cmd[++idx])
	{
		jdx = -1;
		while (cmd[idx][++jdx])
		{
			if (cmd[idx][jdx] == '\'')
			{
				if (!quote)
					quote = cmd[idx][jdx];
				else
					quote = 0;
				printf("quote: %c\n", quote);
			}
			if (cmd[idx][jdx] == '$' && !quote)
			{
				if (cmd[idx][jdx + 1] == '?')
				{
					// free(cmd[idx]);
					// TODO: FIND A WAY TO GET THE EXIT STATUS
					// cmd[idx] = ft_sprintf("%d", EXIT_STATUS_CODE);
					break ;
				}
				tmp = get_the_variable(cmd[idx]);
				free(cmd[idx]);
				cmd[idx] = ft_strdup(tmp);
				free(tmp);
				tmp = NULL;
			}
		}
	}
	return (cmd);
}
