/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/10 07:11:34 by dgomez-m         ###   ########.fr       */
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
#define ERR_INVALID_CHAR "\nexport not an identifier: "
#define ERR_INVALID_CTXT "\nexport: not valid in this context: "
#define ERR_SPACES_IN_VAR "\nexport: bad assignment "
#define UNSET_NOT_ARG "\nunset: not enough arguments "

typedef struct s_my_env
{
	char	*name;
	char	*value;
	void	*next;
}	t_my_env;


typedef struct s_shell
{
	char		*user;
	char		*env;
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
t_my_env	*ft_envnew(void *name, void *value);
void add_env(t_my_env **env, t_my_env *new);


#endif
