/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/04 05:23:34 by alberrod         ###   ########.fr       */
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
	TOKEN_TYPE_FILE,
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
} Token_Type;

typedef struct s_token
{
	Token_Type  type;
	const char *text;
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

// lexer.c
void   lexer(const char *input);

#endif
