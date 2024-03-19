/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/19 11:11:56 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdbool.h>
#define ERR_INVALID_CHAR "\nexport not an identifier: "
#define ERR_INVALID_CTXT "\nexport: not valid in this context: "
#define ERR_SPACES_IN_VAR "\nexport: bad assignment "
#define UNSET_NOT_ARG "\nunset: not enough arguments "
#define ERR_DIR_NOT_FOUND "\ncd: no such file or directory: "
#define SPLIT_QUOTE " \t\n\v\f\r"
#define CMD_NOT_FOUND "\ncommand not found :"

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

typedef struct s_my_env
{
	char	*name;
	char	*value;
	void	*next;
	void 	*prev;
}	t_my_env;


typedef struct s_shell
{
	char		*user;
	char		*env;
	char		*path;
	char		**my_env;
	t_my_env	*env_list;
	char		*prompt;
	char		*input;
	char		*home;
	char		**dolarvar;
}	t_shell;

void get_things(t_shell *shell);
void ft_getenv(t_shell *shell, char **my_env);
//builts in
void command_handler(t_shell *shell);
void cd(t_shell *shell);
void export(t_shell *shell);
void unset(t_shell *shell);
int ft_strlen_pp(char **container);
//error
void ft_error(char *str,char *aux);
void ft_error_cmd(char *str,char *aux);
t_my_env	*ft_envnew(void *name, void *value, t_my_env *new_l);
void add_env(t_my_env **env, t_my_env *new);
void delone_env(t_shell *shell);
void ft_env_split(t_shell *shell);
void print_env(t_my_env *env);
void echo(t_shell *shell);
char *search_things(t_shell *shell, char *search);
void exec_cmd(t_shell *shell);
// lexer.c
t_input   lexer(const char *input);
void cleanup_cmd_list(t_input *cmd_list);

// testers.c
void    test_lexer(t_input *cmd_list);

// parser.c
t_command   *parser(const char *input);

// split_cmd.c
char	**ft_split_cmd(char const *s);



#endif
