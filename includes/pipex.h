/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:16:32 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/23 17:07:23 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
// personal libraries
# include "libft.h"
# include "minishell.h"

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"
# define ERR_PIPE "Pipe"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_ENVP "Environment"
# define ERR_HEREDOC "Here_doc"

// list
typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*env_path;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		*pipe;
	int		idx;
}			t_pipex;

void		send_error(char *str);

int			msg_error(char *str);
int			check_numargc(char *argv, t_pipex *pipex);
t_pipex		init_pipex(int argc, char **argv, char **envp);
char		*create_path(char **envp);
void		here_doc(char *argv, t_pipex *pipex);
void		child(t_pipex p, char **argv, char **envp);
void		child_free(t_pipex *pipex);
void		dad_free(t_pipex *pipex);
void		close_pipes(t_pipex *pipex);
int			main_pipex(int argc, char **argv, char **envp);
#endif