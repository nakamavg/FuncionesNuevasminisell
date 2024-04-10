/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:46:59 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/11 01:47:55 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unix_error(char *mssg, char *str)
{
	if (!str)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", mssg, strerror(errno));
	else
		ft_fd_printf(STDERR_FILENO, "<%s> %s: %s\n",
			str, mssg, strerror(errno));
	exit (127);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		unix_error("fork error", NULL);
	return (pid);
}

char	*extract_path(char *raw_path, char *cmd)
{
	char	**path_array;
	char	*exec_path;
	int		idx;

	path_array = ft_split(raw_path, ':');
	if (!path_array)
		return (NULL);
	idx = 0;
	while (path_array[idx])
	{
		exec_path = ft_sprintf("%s/%s", path_array[idx], cmd);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(path_array[idx++]);
		free(exec_path);
	}
	free(path_array);
	return (NULL);
}

void	exec_cmd(char **cmd, t_shell *shell)
{
	char	*path;

	if (run_builtin(shell, cmd))
		exit (EXIT_SUCCESS);
	if (!ft_strchr(cmd[0], '/'))
		path = extract_path(shell->path, cmd[0]);
	else
	{
		if (access(cmd[0], X_OK) == 0)
			path = ft_strdup(cmd[0]);
		else
			path = NULL;
	}
	if (!path)
		unix_error("command error", cmd[0]);
	if (execve(path, cmd, shell->my_env) == -1)
	{
		free(path);
		unix_error("execve error", NULL);
	}
}
