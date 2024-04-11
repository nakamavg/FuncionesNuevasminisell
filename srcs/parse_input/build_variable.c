/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:22:03 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/11 19:25:12 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	free_sent(char **sent)
{
	int	idx;

	if (!sent)
		return ;
	idx = 0;
	while (sent[idx])
	{
		if (sent[idx])
		{
			free(sent[idx]);
			idx++;
		}
	}
	sent[idx] = NULL;
}

char	*get_the_variable(char *cmd, t_shell *shell)
{
	int		idx;
	int		jdx;
	char	**sent;
	char	*out;
	char	*expanded;

	idx = -1;
	sent = ft_calloc(4, sizeof(char *));
	while (cmd[++idx])
	{
		if (cmd[idx] == '$')
		{
			free_sent(sent);
			sent[0] = ft_substr(cmd, 0, idx);
			jdx = 0;
			while ((cmd[idx + jdx] && !ft_isspace(cmd[idx + jdx]))
				&& cmd[idx + jdx] != '"' && cmd[idx + jdx] != '\''
				&& cmd[idx + jdx] != '=')
				jdx++;
			sent[1] = ft_substr(cmd, idx + 1, jdx - 1);
			sent[2] = ft_substr(cmd, idx + jdx, ft_strlen(cmd) - idx - jdx);
		}
	}
	expanded = search_expand(shell, sent[1]);
	out = ft_sprintf("%s%s%s", sent[0], expanded, sent[2]);
	return (free_sent(sent), free(sent), free(cmd), free(expanded), out);
}


int	handle_quote(char c, int quote, int type)
{
	if (c == type && !quote)
		return (c);
	else if (c == type && quote)
		return (0);
	return (quote);
}
static int	replace_with_global(char **cmd, int idx, int jdx)
{
	if (cmd[idx][jdx + 1] == '?')
	{
		free(cmd[idx]);
		cmd[idx] = ft_sprintf("%d", g_status);
		return (1);
	}
	return (0);
}

char	**expand_variable(char **cmd, t_shell *shell)
{
	int		idx;
	int		jdx;
	int		s_quote;
	int		d_quote;

	idx = -1;
	s_quote = 0;
	d_quote = 0;
	while (cmd[++idx])
	{
		jdx = -1;
		while (cmd[idx][++jdx])
		{
			s_quote = handle_quote(cmd[idx][jdx], s_quote, '\'');
			d_quote = handle_quote(cmd[idx][jdx], d_quote, '"');
			if (cmd[idx][jdx] == '$' && (!s_quote || (s_quote && d_quote)))
			{
				if (replace_with_global(cmd, idx, jdx))
					continue ;
				else if (cmd[idx][jdx + 1] == '\0')
					continue ;
				cmd[idx] = get_the_variable(cmd[idx], shell);
				jdx = -1;
			}
		}
	}
	return (cmd);
}
