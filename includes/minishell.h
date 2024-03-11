/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/11 20:09:31 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef enum {

	TOKEN_TYPE_UNKNOWN,
	TOKEN_TYPE_REDIR_IN,
	TOKEN_TYPE_REDIR_OUT,
	TOKEN_TYPE_REDIR_APPEND,
	TOKEN_TYPE_REDIR_HEREDOC,
	TOKEN_TYPE_PIPE,
	TOKEN_TYPE_EOF,
	TOKEN_TYPE_COMMAND,
	TOKEN_TYPE_IN_FILE,
	TOKEN_TYPE_OUT_FILE,
	TOKEN_TYPE_EQUALS,
	TOKEN_TYPE_EXCLAMATION,
	TOKEN_TYPE_AMPERSAND,
	TOKEN_TYPE_WILDCARD,
	TOKEN_TYPE_BACKTICK,
	TOKEN_TYPE_SEMICOLON,
	TOKEN_TYPE_BACKSLASH,
	TOKEN_TYPE_DOLLAR,
	TOKEN_TYPE_DOT,
	TOKEN_TYPE_QUESTION,
	TOKEN_TYPE_SINGLE_QUOTE,
	TOKEN_TYPE_DOUBLE_QUOTE,
	TOKEN_TYPE_OPEN_PARENTHESIS,
	TOKEN_TYPE_CLOSE_PARENTHESIS,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_VAR,
	TOKEN_TYPE_EXPAND,
	TOKEN_TYPE_MAX
} Token_Type;

typedef struct s_token
{
	Token_Type  type;
	char        *text;
//	char        *value;
	size_t      text_length;
	int         initial_idx;
	int         exec_position;
	struct s_token *next_token;
	struct s_token *prev_token;
} t_token;

typedef struct s_input
{
	t_token *head;
	t_token *token;
} t_input;

typedef struct s_command
{
	char    **cmds;
	char    *infile;
	char    *outfile;
	int     infile_fd;
	int     outfile_fd;
} t_command;

// lexer.c
t_input   *lexer(const char *input);
void cleanup_input_struct(t_input *input_struct);

// testers.c
void    test_lexer(t_input *input_struct);

// parser.c
t_command   *parser(const char *input);
#endif

