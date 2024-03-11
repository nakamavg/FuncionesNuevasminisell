/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/11 20:09:48 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *set_infile(t_input *input_struct) {
	while (input_struct->token)
	{
		if (input_struct->token->type == TOKEN_TYPE_REDIR_IN)
			return (input_struct->token->next_token->text);
		input_struct->token = input_struct->token->next_token;
	}
	return (NULL);
}

char    *set_outfile(t_input *input_struct) {
	while (input_struct->token)
	{
		if (input_struct->token->type == TOKEN_TYPE_REDIR_OUT)
			return (input_struct->token->next_token->text);
		input_struct->token = input_struct->token->next_token;
	}
	return (NULL);
}


void parse_input(t_input *input_struct, t_command *exec_line) {

	exec_line->infile = set_infile(input_struct);
	exec_line->outfile = set_outfile(input_struct);

	return ;
}

t_command   *parser(const char *input)
{
	t_command *exec_line;
	t_input *input_struct;

	exec_line = malloc(sizeof(t_command));
	input_struct = lexer(input);
	if (!input_struct)
		return (printf("Error in the lexer\n"), NULL);
	parse_input(input_struct, exec_line);
	cleanup_input_struct(input_struct);
	return (exec_line);
}
