/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/16 21:49:18 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define ERR_DIR_NOT_FOUND "\ncd: no such file or directory: "

# define RESET "\001\e[0m\002"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"

typedef enum s_Token_Type
{
	TOKEN_TYPE_UNKNOWN,
	TOKEN_TYPE_REDIR_IN,
	TOKEN_TYPE_REDIR_OUT,
	TOKEN_TYPE_REDIR_APPEND,
	TOKEN_TYPE_REDIR_HEREDOC,
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
	t_input			parsed_input;
}					t_shell;

extern int			g_status;

// /parse_input/parser.c
int					sanitize_input(const char *input);
int					parse_input(t_shell *shell);

// /parse/input/build_cmd.c
t_input				init_input(void);
void				cleanup_cmd_list(t_input *cmd_list);
void				build_cmdlst(const char *input, t_shell *shell);

// /parse/input/build_split.c
char				**cmd_split(const char *text, char *in, char *out);

// /parse/input/build_split_utils.c
ssize_t				break_content(const char *s, char c, char **out);
size_t				count_words(char const *s, char c);
void				free_output(char **output, size_t counter);

// /parse/input/build_pipe.c
t_cmd				*init_pipe(const char *text, size_t text_length,
						int initial_idx, t_shell *shell);
void				add_pipe(t_input *cmd_list, t_cmd *new_token);

// /parse/input/build_io.c
t_Token_Type		ft_infile_mode(const char *input, char *last_redir);
char                *ft_infile_content(const char *input, int s_quote, int d_quote);
t_Token_Type		ft_outfile_mode(const char *input);
char				*ft_outfile_content(const char *input);

// /parse/input/build_variable.c
char				*get_the_variable(char *cmd, t_shell *shell);
char				**expand_variable(char **cmd, t_shell *shell,
						int s_quote, int d_quote);

// /parse/input/handle_quotes.c
void				set_quote(int *s_quote, int *d_quote, char c);
int					handle_quote(char c, int quote, int *compare, int type);

// /parse/input/build_variable_utils.c
bool				search_token(char *cmd, int idx, int jdx);

// split_cmd.c

// pipes_raw.c
pid_t				fork_process(void);

// pipes/manage_files.c
int					out_file_open(char *file_write, t_Token_Type write_type);
void				out_file_create(char *file_write);
int					in_file_open(char *file_read, t_Token_Type infile_mode);

// pipes/run_pipes.c
void				run_pipes(t_shell *shell, t_input cmd_input, t_cmd *pipe);
void				run_process(char **cmd, t_shell *shell, int pipe_in[2],
						int pipe_out[2]);
int					set_g_status(int status);
void				create_pipes(int pipe_fd[2]);

// pipes/aux_run_pipes.c
void				handle_outfile_and_next_cmd(t_cmd *pipe, int *next_pipe);
void				handle_infile(t_cmd *pipe, t_input cmd_input,
						int *prev_pipe);
void				run_process_if(t_cmd *pipe, t_shell *shell, int *p_pipe,
						int *n_pipe);

// pipes/process_utils.c
void				unix_error(char *mssg, char *str);
char				*extract_path(char *raw_path, char *cmd);
void				exec_cmd(char **cmd, t_shell *shell);
// pipes/pipes_utils.c
void				dup_and_close_fds(int pipe_fd[2], int std_fd);
void				pipe_fd(int *in, int *out);

// errors.c
void				ft_error(char *str, char *aux);

// gethings.c
char				*search_expand(t_shell *shell, char *search);
char				*search_things(t_shell *shell, char *search,
						char **original);
void				get_things(t_shell *shell, bool update);
void				ft_getenv(t_shell *shell, char **env);
void				ft_env_split(t_shell *shell);

// get_things_aux.c
int					ft_strlen_pp(char **container);
void				print_env(t_my_env *env);

// utilslist.c
t_my_env			*ft_envnew(void *name, void *value, t_my_env *new_l);
void				add_env(t_my_env **env, t_my_env *new);
void				delone_env(t_my_env *shell);

// cmd_handler.c
void				command_handler(t_shell *shell);
int					run_builtin(t_shell *shell, char **cmd);

// cd.c
int					cd(t_shell *shell, char **cmd);

// echo.c
void				echo(char **cmd);
char				*search_echo(t_shell *shell, char *search);
int					check_names(char *name, char *search);

// export.c
int					export(t_shell *shell, char **cmd);
bool				check_if_exist(t_shell *env, char *name, char *value);

// export_utils.c
void				handle_errors_export(char *input, bool *local_error);
t_my_env			*go_to_end(t_my_env *env);
void				sort_env(t_my_env *env);

// exit.c
int					exit_shell(t_shell *shell, char **cmd);

// free_shell.c
void				free_shell(t_shell *shell);
void				free_array_of_strings(char **env);
void				free_env(t_shell *shell);

// unset.c
void				unset(t_shell *shell, char **cmd);

// pwd.c
void				pwd(void);

#endif
