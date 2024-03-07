/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:37:31 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/07 17:15:55 by dgomez-m         ###   ########.fr       */
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



typedef struct s_shell
{
	char	*user;
	char	*env;
	char	**my_env;
	char	*prompt;
	char	*input;
	char	*home;
	char	**dolarvar;
}	t_shell;

void get_things(t_shell *shell);
void ft_getenv(t_shell *shell, char **my_env);
//builts in
void command_handler(t_shell *shell);
void cd(t_shell *shell);
void export(t_shell *shell);
int ft_strlen_pp(char **container);

#endif
