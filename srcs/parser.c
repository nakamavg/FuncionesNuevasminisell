/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/10 23:46:20 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char    *set_infile(t_input *input_struct) {
//	char *infile;
//
//	infile = NULL;
//	while (input_struct->token)
//	{
//		if (input_struct->token->type == TOKEN_TYPE_REDIR_IN)
//		{
//			infile = input_struct->token->next_token->text;
//			input_struct->token = input_struct->token->next_token;
//		}
//		input_struct->token = input_struct->token->next_token;
//
//	if (input_struct->token->type == TOKEN_TYPE_REDIR_IN) {
//		infile = input_struct->token->next_token->text;
//		input_struct->token = input_struct->token->next_token;
//	}
//	return (infile);
//}
//
//char **parse_input(t_input *input_struct) {
//	char **output;
//	int     argc;
//
//	argc = 0;
//	output[argc] = NULL;
//
//
//
//}

char    **parser(const char *input) {
	char **output;
	t_input *input_struct;

	input_struct = lexer(input);
	if (!input_struct)
		return (printf("Error in the lexer\n"), NULL);
	output = NULL;
	return (output);
}
