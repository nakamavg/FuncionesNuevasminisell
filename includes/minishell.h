/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 20:38:01 by alberrod         ###   ########.fr       */
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
	TOKEN_TYPE_AMPERSAND,
	TOKEN_TYPE_WILDCARD,
	TOKEN_TYPE_DOLLAR,
	TOKEN_TYPE_DOT,
	TOKEN_TYPE_QUESTION,
	TOKEN_TYPE_SINGLE_QUOTE,
	TOKEN_TYPE_DOUBLE_QUOTE,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_VAR,
	TOKEN_TYPE_EXPAND,
	TOKEN_TYPE_MAX
} Token_Type;



typedef struct s_cmd
{
	char        *text;
	char		*infile;
	Token_Type	infile_mode;
	char		*outfile;
	int			write_mode;
	char		**cmd_list;
	struct s_cmd *next_cmd;
	struct s_cmd *prev_token;
} t_cmd;

typedef struct s_input
{
	t_cmd *head;
	t_cmd *token;
} t_input;

typedef struct s_command
{
	char    **cmds;
	char    *infile;
	char    *outfile;
	int     infile_fd;
	int     outfile_fd;
	char	*eof; // if eof is NULL, it's a regular file. Else, here_doc required
	int     write_mode;
} t_command;

// lexer.c
t_input   lexer(const char *input);
void cleanup_cmd_list(t_input *cmd_list);

// testers.c
void    test_lexer(t_input *cmd_list);

// parser.c
t_command   *parser(const char *input);
#endif

