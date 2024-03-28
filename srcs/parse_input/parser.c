/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/28 17:59:01 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * sq_sent: single quotes sentence
 * dq_sent: double quotes sentence
*/
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
			while (ft_isspace(input[++cursor]))
				;
			if (input[cursor] == '|')
				return (printf("Error: two pipes, no cmds in between\n"), 1);
		}
		input++;
	}
	if (within_sq_sent || within_dq_sent)
		return (printf("Error: Not closed string used as input\n"), 1);
	// return (printf("input sanitized\n"), 0);
	return (0);
}

void	parse_input(t_shell *shell)
{
	// t_input	cmd_list;

	shell->parsed_input = init_input();
	// printf("input: %s\n", shell->input);
	if (sanitize_input(shell->input))
	{
		printf("non-valid input\n");
		return ;
	}
	// build_cmdlst(shell->input, &shell->parsed_input);
	build_cmdlst(shell->input, shell);
	// test_lexer(&cmd_list);
	return ;
}
