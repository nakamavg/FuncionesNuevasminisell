/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/22 22:46:12 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_redir_sanitize(const char *c, int within_dq_sent,
		int within_sq_sent)
{
	if ((c[0] == '>' || c[0] == '<') && !within_dq_sent && !within_sq_sent)
		if (!c[1])
			return (1);
	return (0);
}

int	sanitize_input(const char *in, int within_dq_sent, int within_sq_sent)
{
	int	i;

	while (in != NULL && *in)
	{
		i = 0;
		if (*in == '\"' && !within_sq_sent)
			within_dq_sent = !within_dq_sent;
		if (*in == '\'' && !within_dq_sent)
			within_sq_sent = !within_sq_sent;
		if (*in == '|' && !within_dq_sent && !within_sq_sent)
		{
			if (!in[1])
				return (1);
			while (in[++i] && (ft_isspace(in[i]) || ft_strchr("\"'<>$", in[i])))
				;
			if (in[i] && in[i] == '|')
				return (1);
		}
		if (is_valid_redir_sanitize(in, within_dq_sent, within_sq_sent))
			return (1);
		in++;
	}
	if (within_sq_sent || within_dq_sent)
		return (1);
	return (0);
}

int	parse_input(t_shell *shell)
{
	shell->parsed_input = init_input();
	if (sanitize_input(shell->input, 0, 0))
	{
		printf("Error: Non-Valid Input\n");
		return (1);
	}
	build_cmdlst(shell->input, shell);
	return (0);
}
