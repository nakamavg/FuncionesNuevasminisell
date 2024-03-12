/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/12 03:18:42 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *init_exec_line()
{
	t_command *exec_line;

	exec_line = malloc(sizeof(t_command));
	exec_line->infile = NULL;
	exec_line->outfile = NULL;
	exec_line->write_mode = O_TRUNC;
	exec_line->eof = NULL;
	return (exec_line);
}

void parse_in_out(t_input *input_struct, t_command *exec_line) {
	t_token *token;

	token = input_struct->head;
	while (token)
	{
		if (token->type == TOKEN_TYPE_REDIR_IN)
			exec_line->infile = token->next_token->text;
		if (token->type == TOKEN_TYPE_REDIR_OUT)
			exec_line->outfile = token->next_token->text;
		if (token->type == TOKEN_TYPE_REDIR_APPEND)
		{
			exec_line->write_mode = O_APPEND;
			exec_line->outfile = token->next_token->text;
		}
		if (token->type == TOKEN_TYPE_REDIR_HEREDOC)
			exec_line->eof = token->next_token->text;
		token = token->next_token;
	}
}

void parse_input(t_input *input_struct, t_command *exec_line) {


	parse_in_out(input_struct, exec_line);
	if (exec_line->infile)
		printf("Infile: %s\n", exec_line->infile);
	if (exec_line->outfile)
		printf("Outfile: %s\n", exec_line->outfile);
	return ;
}

t_command   *parser(const char *input)
{
	t_command *exec_line;
	t_input *input_struct;

	exec_line = init_exec_line();
	input_struct = lexer(input);
	if (!input_struct)
		return (printf("Error in the lexer\n"), NULL);
	parse_input(input_struct, exec_line);
	cleanup_input_struct(input_struct);
	return (exec_line);
}
