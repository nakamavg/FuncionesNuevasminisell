/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/10 23:26:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_lexer(t_input *input_struct) {
	const char *token_type_names[] = {
			"TOKEN_TYPE_UNKNOWN",
			"TOKEN_TYPE_REDIR_IN",
			"TOKEN_TYPE_REDIR_OUT",
			"TOKEN_TYPE_REDIR_APPEND",
			"TOKEN_TYPE_REDIR_HEREDOC",
			"TOKEN_TYPE_PIPE",
			"TOKEN_TYPE_EOF",
			"TOKEN_TYPE_COMMAND",
			"TOKEN_TYPE_IN_FILE",
			"TOKEN_TYPE_OUT_FILE",
			"TOKEN_TYPE_EQUALS",
			"TOKEN_TYPE_EXCLAMATION",
			"TOKEN_TYPE_AMPERSAND",
			"TOKEN_TYPE_WILDCARD",
			"TOKEN_TYPE_BACKTICK",
			"TOKEN_TYPE_SEMICOLON",
			"TOKEN_TYPE_BACKSLASH",
			"TOKEN_TYPE_DOLLAR",
			"TOKEN_TYPE_DOT",
			"TOKEN_TYPE_QUESTION",
			"TOKEN_TYPE_SINGLE_QUOTE",
			"TOKEN_TYPE_DOUBLE_QUOTE",
			"TOKEN_TYPE_OPEN_PARENTHESIS",
			"TOKEN_TYPE_CLOSE_PARENTHESIS",
			"TOKEN_TYPE_STRING",
			"TOKEN_TYPE_VAR",
			"TOKEN_TYPE_EXPAND"
	};
	input_struct->token = input_struct->head;
	while (input_struct->token) {
		printf("Token: %s\n\ttext_len: %lu\n\ttype: %s\n", input_struct->token->text, input_struct->token->text_length,
		       token_type_names[input_struct->token->type]);
		input_struct->token = input_struct->token->next_token;
	}
	printf("Head: %s\n", input_struct->head->text);
	// for (int i = 0; i < TOKEN_TYPE_MAX; i++) {
	//     printf("%s is %d\n", token_type_names[i], i);
	// }
}
