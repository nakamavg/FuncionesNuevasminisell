/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 04:58:36 by dgomez-m         ###   ########.fr       */
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


typedef struct s_cmd
{
	pid_t			pid;
	int				pipe[2];
	int				intfile;
	int				outfile;
	char			**cmd;
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*back;
}	t_cmd;

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


#endif
