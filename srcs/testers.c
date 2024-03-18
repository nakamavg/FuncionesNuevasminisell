/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/18 19:51:14 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_lexer(t_input *cmd_list) {
	// const char *token_type_names[] = {
	// 		"TOKEN_TYPE_UNKNOWN",
	// 		"TOKEN_TYPE_REDIR_IN",
	// 		"TOKEN_TYPE_REDIR_OUT",
	// 		"TOKEN_TYPE_REDIR_APPEND",
	// 		"TOKEN_TYPE_REDIR_HEREDOC",
	// 		"TOKEN_TYPE_PIPE",
	// 		"TOKEN_TYPE_EOF",
	// 		"TOKEN_TYPE_COMMAND",
	// 		"TOKEN_TYPE_IN_FILE",
	// 		"TOKEN_TYPE_OUT_FILE",
	// 		"TOKEN_TYPE_EQUALS",
	// 		"TOKEN_TYPE_EXCLAMATION",
	// 		"TOKEN_TYPE_AMPERSAND",
	// 		"TOKEN_TYPE_WILDCARD",
	// 		"TOKEN_TYPE_BACKTICK",
	// 		"TOKEN_TYPE_SEMICOLON",
	// 		"TOKEN_TYPE_BACKSLASH",
	// 		"TOKEN_TYPE_DOLLAR",
	// 		"TOKEN_TYPE_DOT",
	// 		"TOKEN_TYPE_QUESTION",
	// 		"TOKEN_TYPE_SINGLE_QUOTE",
	// 		"TOKEN_TYPE_DOUBLE_QUOTE",
	// 		"TOKEN_TYPE_OPEN_PARENTHESIS",
	// 		"TOKEN_TYPE_CLOSE_PARENTHESIS",
	// 		"TOKEN_TYPE_STRING",
	// 		"TOKEN_TYPE_VAR",
	// 		"TOKEN_TYPE_EXPAND"
	// };
	cmd_list->token = cmd_list->head;
	while (cmd_list->token) {
		if (cmd_list->token->text)
		printf("\nCMD: %s\n\tthe infile is: %s\n\tthe oufile is: %s\n", cmd_list->token->text, cmd_list->token->infile, cmd_list->token->outfile);
		cmd_list->token = cmd_list->token->next_cmd;
	}
	// printf("Head: %s\n", cmd_list->head->text);
	// for (int i = 0; i < TOKEN_TYPE_MAX; i++) {
	//     printf("%s is %d\n", token_type_names[i], i);
	// }
}
