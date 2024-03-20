/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 17:36:17 by alberrod         ###   ########.fr       */
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

// testers.c
void		test_lexer(t_input *cmd_list);

// /parse_input/parser.c
int			sanitize_input(const char *input);
t_input		parse_input(const char *input);

// /parse/input/build_cmd.c
t_input		init_input();
void		build_cmdlst(const char *input, t_input *cmd_list);
void		cleanup_cmd_list(t_input *cmd_list);

// /parse/input/build_split.c
char		**cmd_split(const char *text, char *in, char *out);

// /parse/input/build_pipe.c
t_cmd		*init_pipe(const char *text, size_t text_length, int initial_idx);
void		add_pipe(t_input *cmd_list, t_cmd *new_token);

// /parse/input/build_io.c
Token_Type	ft_infile_mode(const char *input);
char		*ft_infile_content(const char *input);
Token_Type	ft_outfile_mode(const char *input);
char		*ft_outfile_content(const char *input);

// /parse/input/build_variable.c
char		*get_the_variable(char *cmd);
char		**expand_variable(char **cmd);

// split_cmd.c
char		**cmd_split(const char *text, char *in, char *out);

#endif

