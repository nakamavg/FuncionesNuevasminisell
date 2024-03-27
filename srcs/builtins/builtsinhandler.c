/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsinhandler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:06:34 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/27 19:24:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// TODO: REPLACE
// static char	*get_cmd(char **paths, char *cmd)
// {
// 	char	*tmp;
// 	char	*command;
// 	int		i;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		command = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(command, X_OK) == 0)
// 			return (command);
// 		free(command);
// 		i++;
// 	}
// 	return (NULL);
// }

// void exec_cmd(t_shell *shell)
// {
// 	pid_t pid;
// 	int status;
// 	char **args;
// 	char *cmd;
// 	// int i;

// 	// i = -1;
// 	args = ft_split(shell->input, ' ');
// 	cmd = get_cmd(ft_split(shell->path, ':'), args[0]);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(cmd, args, shell->my_env) == -1)
// 			ft_error_cmd(CMD_NOT_FOUND, args[0]);
// 	}
// 	else if (pid < 0)
// 		ft_putstr_fd("fork failed \n", STDOUT_FILENO);
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	free(args);
// }

//////////


// void more_cmd_handler(t_shell *shell)
// {
// 	if(ft_strncmp(shell->input,"$USER", 5) == 0)
// 	return((void)printf("%s", shell->user));
// 	else if(ft_strncmp(shell->input,"$PATH", 5) == 0)
// 	return((void)printf("%s", shell->env));
// 	else if(ft_strncmp(shell->input,"$HOME", 5) == 0)
// 	return((void)printf("%s", shell->home));
// 	else
// 		exec_cmd(shell);
		
// }

int run_builtin(t_shell *shell)
{
	char *cmd;

	cmd = shell->parsed_input.head->cmd_list[0];
	if (!ft_strncmp(cmd,  "echo", ft_strlen(cmd)))
		return(echo(shell->parsed_input.head->cmd_list), 1);
	if (!ft_strncmp(cmd,  "env", ft_strlen(cmd)))
		return(print_env(shell->env_list), 1);
	if (!ft_strncmp(cmd,  "exit", ft_strlen(cmd)))
		return(exit(0), 1);
	if (!ft_strncmp(cmd,  "pwd", ft_strlen(cmd)))
		return ((void)printf("%s\n", getcwd(NULL, 0)), 1);
	if (!ft_strncmp(cmd,  "cd", ft_strlen(cmd)))
		return(cd(shell), 1);
	if (!ft_strncmp(cmd,  "export", ft_strlen(cmd)))
		return(export(shell), 1);
	if (!ft_strncmp(cmd,  "unset", ft_strlen(cmd)))
		return(unset(shell), 1);
	return (0);
}

void command_handler(t_shell *shell)
{
	if (!shell->parsed_input.head->next_cmd)
		if (run_builtin(shell))
			return ;
	run_pipes(shell, shell->parsed_input, shell->parsed_input.head);
}
