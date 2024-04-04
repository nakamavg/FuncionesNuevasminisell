/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/04 03:30:55 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "libft.h"
// # include <stdio.h>
// # include <fcntl.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <errno.h>
// # include <sys/wait.h>

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define OUT STDOUT_FILENO
# define IN STDIN_FILENO
# define ERR_INVALID_CHAR "\nexport: not an identifier: "
# define ERR_INVALID_CTXT "\nexport: not valid in this context: "
# define ERR_SPACES_IN_VAR "\nexport: bad assignment "
# define UNSET_NOT_ARG "\nunset: not enough arguments "
# define ERR_DIR_NOT_FOUND "\ncd: no such file or directory: "
# define SPLIT_QUOTE " \t\n\v\f\r"
# define CMD_NOT_FOUND "\ncommand not found :"
# define ERR_TOO_MANY_ARGS "\nexit: too many arguments"
# define ERR_NUM_EXPECTED "exit: numeric argument required\n"

typedef enum s_Token_Type
{
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
}					t_Token_Type;

typedef enum s_Builtin
{
	ECH0 = 42,
	ENV = 43,
	EXIT = 44,
	PWD = 45,
	CD = 46,
	EXPORT = 47,
	UNSET = 48,
	NONE = 0
}					t_Builtin;

typedef struct s_cmd
{
	char			*text;
	char			*infile;
	t_Token_Type	infile_mode;
	char			*outfile;
	int				write_mode;
	char			**cmd_list;
	struct s_cmd	*next_cmd;
	struct s_cmd	*prev_token;
}					t_cmd;

typedef struct s_input
{
	t_cmd			*head;
	t_cmd			*token;
}					t_input;

typedef struct s_command
{
	char			**cmds;
	char			*infile;
	char			*outfile;
	int				infile_fd;
	int				outfile_fd;
	char			*eof;
	int				write_mode;
}					t_command;

typedef struct s_my_env
{
	char			*name;
	char			*value;
	void			*next;
	void			*prev;
}					t_my_env;

typedef struct s_shell
{
	char			*user;
	char			*env;
	char			*path;
	char			**my_env;
	t_my_env		*env_list;
	t_my_env		*env_sys_end;
	char			*prompt;
	char			*input;
	char			*home;
	char			**dolarvar;
	t_input			parsed_input;
}					t_shell;

extern int			global_status;

// testers.c
void				test_lexer(t_input *cmd_list);

// /parse_input/parser.c
int					sanitize_input(const char *input);
// t_input			parse_input(const char *input);
void				parse_input(t_shell *shell);

// /parse/input/build_cmd.c
t_input				init_input(void);
// void			build_cmdlst(const char *input, t_input *cmd_list);
void				cleanup_cmd_list(t_input *cmd_list);
void				build_cmdlst(const char *in, t_shell *shell);

// /parse/input/build_split.c
char				**cmd_split(const char *text, char *in, char *out);

// /parse/input/build_pipe.c
// t_cmd			*init_pipe(const char *text,
// 					size_t text_length, int initial_idx);
t_cmd				*init_pipe(const char *text, size_t text_length,
						int initial_idx, t_shell *shell);
void				add_pipe(t_input *cmd_list, t_cmd *new_token);

// /parse/input/build_io.c
t_Token_Type		ft_infile_mode(const char *input);
char				*ft_infile_content(const char *input);
t_Token_Type		ft_outfile_mode(const char *input);
char				*ft_outfile_content(const char *input);

// /parse/input/build_variable.c
// char			*get_the_variable(char *cmd);
char				*get_the_variable(char *cmd, t_shell *shell);
// char			**expand_variable(char **cmd);
char				**expand_variable(char **cmd, t_shell *shell);

// split_cmd.c
char				**cmd_split(const char *text, char *in, char *out);

// pipes_raw.c
// void 			run_pipes(t_input cmd_input, t_cmd *pipe, char **envp);
pid_t				fork_process(void);

// pipes/manage_files.c
int					out_file_open(char *file_write, t_Token_Type write_type);
void				out_file_create(char *file_write);
// int				in_file_open(char *file_read);
int					in_file_open(char *file_read, t_Token_Type infile_mode);

// pipes/run_pipes.c
void				run_pipes(t_shell *shell, t_input cmd_input, t_cmd *pipe);
void				run_process(char **cmd, t_shell *shell, int pipe_in[2],
						int pipe_out[2]);
void				set_null_pipe(int *in, int *out);
int					set_global_status(int status);
void				create_pipes(int pipe_fd[2]);
// pipes/process_utils.c
void				unix_error(char *mssg, char *str);
pid_t				fork_process(void);
char				*extract_path(char *raw_path, char *cmd);
void				exec_cmd(char **cmd, t_shell *shell);
// pipes/pipes_utils.c
void				create_pipes(int pipe_fd[2]);
void				dup_and_close_fds(int pipe_fd[2], int std_fd);
void				set_null_pipe(int *in, int *out);
int					set_global_status(int status);

////////

// errors.c
void				ft_error3(char *str);
void				ft_error_cmd(char *str, char *aux);
void				ft_error(char *str, char *aux);

// gethings.c
char				*search_expand(t_shell *shell, char *search);
char				*search_things(t_shell *shell, char *search);
void				get_things(t_shell *shell);
int					ft_strlen_pp(char **container);
void				ft_getenv(t_shell *shell, char **env);
void				ft_env_split(t_shell *shell);
void				print_env(t_my_env *env);

// utilslist.c
t_my_env			*ft_envnew(void *name, void *value, t_my_env *new_l);
void				add_env(t_my_env **env, t_my_env *new);
void				delone_env(t_my_env *shell);
void				add_env_back(t_my_env **env, t_my_env *new);

// cmd_handler.c
void				command_handler(t_shell *shell);
int					run_builtin(t_shell *shell);

// cd.c
// void				cd(t_shell *shell);
int					cd(t_shell *shell, char **cmd);

// echo.c
void				echo(char **cmd);
char				*search_echo(t_shell *shell, char *search);
int					check_names(char *name, char *search);

// export.c
int					export(t_shell *shell, char **cmd);
bool				check_if_exist(t_shell *env, char *name, char *value);
// export_utils.c
void				handle_errors_export(char *input,bool *local_error);
t_my_env			*go_to_end(t_my_env *env);
void 				sort_env(t_my_env *env);

// exit.c
int					exit_shell(t_shell *shell, char **cmd);
// free_shell.c
void				free_shell(t_shell *shell);

// unset.c
void				unset(t_shell *shell, char **cmd);

// free_shell.c

#endif
