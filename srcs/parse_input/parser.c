/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/22 21:15:19 by alberrod         ###   ########.fr       */
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

int	sanitize_input(const char *input, int within_dq_sent, int within_sq_sent)
{
	int	i;

	while (input != NULL && *input)
	{
		i = 0;
		if (*input == '\"' && !within_sq_sent)
			within_dq_sent = !within_dq_sent;
		if (*input == '\'' && !within_dq_sent)
			within_sq_sent = !within_sq_sent;
		if (*input == '|' && !within_dq_sent && !within_sq_sent)
		{
			if (!input[1])
				return (1);
			while (input[++i] && (ft_isspace(input[i]) || ft_strchr("\"'<>$", input[i])))
				;
			if (input[i] == '|')
				return (1);
		}
		if (is_valid_redir_sanitize(input, within_dq_sent, within_sq_sent))
			return (1);
		input++;
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
