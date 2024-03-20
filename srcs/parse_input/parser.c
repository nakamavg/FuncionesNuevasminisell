/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 17:36:23 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sanitize_input(const char *input)
{
	int within_dq_sentence = 0;
	int within_sq_sentence = 0;
	int cursor = 0;

	while (*input)
	{
		if (*input == '\"' && !within_sq_sentence)
			within_dq_sentence = !within_dq_sentence;
		if (*input == '\'' && !within_dq_sentence)
			within_sq_sentence = !within_sq_sentence;
		if (*input == '|' && !within_dq_sentence && !within_sq_sentence)
		{
			while (ft_isspace(input[++cursor]))
				;
			if (input[cursor] == '|')
				return (printf("Error: two pipes without commands in between\n"), 1);
			cursor = 0;
		}
		input++;
	}
	if (within_sq_sentence || within_dq_sentence)
		return (printf("Error: Not closed string used as input\n"), 1);
	return (printf("input sanitized\n"), 0);
}

t_input   parse_input(const char *input)
{
	t_input cmd_list;

	cmd_list = init_input();
	printf("input: %s\n", input);
	if (sanitize_input(input))
		return (printf("non-valid input\n"), cmd_list);
	build_cmdlst(input, &cmd_list);
	test_lexer(&cmd_list);

	return (cmd_list);
}