/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:22:03 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/21 20:39:59 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_sent(char *sent[3])
{
	int	idx;

	if (!*sent)
		return ;
	idx = 3;
	while (idx)
	{
		if (sent[--idx])
		{
			free(sent[idx]);
			sent[idx] = NULL;
		}
	}
}

// TODO: USE OUR OWN VERSION OF GETENV
// out = ft_sprintf("%s%s%s", begin, getenv(sent[1]), end);
// The sent (sentence) is structured: 0 - begin, 1 - variable, 2 - end

char	*get_the_variable(char *cmd)
{
	int		idx;
	int		jdx;
	char	*sent[3];
	char	*out;

	idx = -1;
	while (cmd[++idx])
	{
		if (cmd[idx] == '$')
		{
			free_sent(sent);
			sent[0] = ft_substr(cmd, 0, idx);
			jdx = 0;
			while ((cmd[idx + jdx] && !ft_isspace(cmd[idx + jdx]))
				&& cmd[idx + jdx] != '\"')
				jdx++;
			sent[1] = ft_substr(cmd, idx + 1, jdx - 1);
			sent[2] = ft_substr(cmd, idx + jdx, ft_strlen(cmd) - idx - jdx);
		}
	}
	out = ft_sprintf("%sOUR_GETENV(%s)%s", sent[0], sent[1], sent[2]);
	free_sent(sent);
	free(cmd);
	return (out);
}

int	handle_quote(char c, int quote)
{
	if (c == '\'' && !quote)
		return (c);
	else if (c == '\'' && quote)
		return (0);
	return (quote);
}

// TODO: FIND A WAY TO GET THE EXIT STATUS
// Build a function similar to get_the_variable but with
// get_the_exit_status
char	**expand_variable(char **cmd)
{
	int		idx;
	int		jdx;
	int		quote;

	idx = -1;
	quote = 0;
	while (cmd[++idx])
	{
		jdx = -1;
		while (cmd[idx][++jdx])
		{
			quote = handle_quote(cmd[idx][jdx], quote);
			if (cmd[idx][jdx] == '$' && !quote)
			{
				if (cmd[idx][jdx + 1] == '?')
					printf("I should print the exit status: $?");
				cmd[idx] = get_the_variable(cmd[idx]);
				jdx = -1;
			}
		}
	}
	return (cmd);
}
