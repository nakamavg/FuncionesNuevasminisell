/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 01:31:44 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:35:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 00:49:24 by alberrod         ###   ########.fr       */
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

// void parse_in_out(t_input *cmd_list, t_command *exec_line) {
// 	t_cmd *token;

// 	token = cmd_list->head;
// 	while (token)
// 	{
// 		if (token->type == TOKEN_TYPE_REDIR_IN)
// 			exec_line->infile = token->next_cmd->text;
// 		if (token->type == TOKEN_TYPE_REDIR_OUT)
// 			exec_line->outfile = token->next_cmd->text;
// 		if (token->type == TOKEN_TYPE_REDIR_APPEND)
// 		{
// 			exec_line->write_mode = O_APPEND;
// 			exec_line->outfile = token->next_cmd->text;
// 		}
// 		if (token->type == TOKEN_TYPE_REDIR_HEREDOC)
// 			exec_line->eof = token->next_cmd->text;
// 		token = token->next_cmd;
// 	}
// }

// void parse_input(t_input *cmd_list, t_command *exec_line) {


// 	parse_in_out(cmd_list, exec_line);
// 	if (exec_line->infile)
// 		printf("Infile: %s\n", exec_line->infile);
// 	if (exec_line->outfile)
// 		printf("Outfile: %s\n", exec_line->outfile);
// 	return ;
// }

t_command   *parser(const char *input)
{
	t_command *exec_line;
	t_input cmd_list;

	exec_line = init_exec_line();
	cmd_list = lexer(input);
//	if (cmd_list.head->text == NULL)
//		return (printf("Error in the lexer\n"), NULL);
	// if (!cmd_list)
	// 	return (printf("Error in the lexer\n"), NULL);
	// parse_input(cmd_list, exec_line);
	cleanup_cmd_list(&cmd_list);
	return (exec_line);
}
