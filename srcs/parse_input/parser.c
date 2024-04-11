/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/11 10:08:49 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sanitize_input(const char *input)
{
	int	within_dq_sent;
	int	within_sq_sent;
	int	cursor;

	within_dq_sent = 0;
	within_sq_sent = 0;
	while (*input)
	{
		cursor = 0;
		if (*input == '\"' && !within_sq_sent)
			within_dq_sent = !within_dq_sent;
		if (*input == '\'' && !within_dq_sent)
			within_sq_sent = !within_sq_sent;
		if (*input == '|' && !within_dq_sent && !within_sq_sent)
		{
			while (ft_isspace(input[++cursor])
				|| ft_strchr("\"'<>$", input[cursor]))
				;
			if (input[cursor] == '|')
				return (printf("Error: two pipes, no cmds in between\n"), 1);
		}
		input++;
	}
	if (within_sq_sent || within_dq_sent)
		return (printf("Error: Not closed string used as input\n"), 1);
	return (0);
}

int	parse_input(t_shell *shell)
{
	shell->parsed_input = init_input();
	if (sanitize_input(shell->input))
	{
		printf("non-valid input\n");
		return (1);
	}
	build_cmdlst(shell->input, shell);
	return (0);
}
