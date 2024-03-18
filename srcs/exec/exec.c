/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:51:59 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/18 08:02:45 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void exec_cmd(t_shell *shell)
{
	pid_t pid;
	int status;
	char **args;
	char *cmd;
	int i;

	i = -1;
	args = ft_split(shell->input, ' ');
	cmd = get_cmd(ft_split(shell->path, ':'), args[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, args, shell->my_env) == -1)
			ft_error_cmd(CMD_NOT_FOUND, args[0]);
	}
	else if (pid < 0)
		ft_putstr_fd("fork failed \n", STDOUT_FILENO);
	else
	{
		waitpid(pid, &status, 0);
	}
	free(args);
}


