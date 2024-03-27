/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsinhandler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:06:34 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/26 23:27:53 by alberrod         ###   ########.fr       */
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

void command_handler(t_shell *shell)
{
	// int pid;

	// pid = fork_process();
	// if (pid == 0)
	run_pipes(shell, shell->parsed_input, shell->parsed_input.head);
	// waitpid(pid, &global_status, 0);
	// return (status);

	// if (ft_strncmp(shell->input, "exit", 4) == 0)
	// 	return(exit(0));
	// else if (ft_strncmp(shell->input, "cd", 2) == 0)
	// 		return(cd(shell));
	// else if (ft_strncmp(shell->input, "pwd", 3) == 0)
	// 	return((void)printf("%s\n", getcwd(NULL, 0)));
	// else if (ft_strncmp(shell->input, "export", 6) == 0)
	// 	return(export(shell)); 
	// else if (ft_strncmp(shell->input, "unset", 5) == 0)
	// 	return(unset(shell)); 
	// else if (ft_strncmp(shell->input, "env", 3) == 0)
	// 	return(print_env(shell->env_list));
	// else if (ft_strncmp(shell->input, "echo", 4) == 0)
	// 	return(echo(shell->parsed_input.head->cmd_list));
	// more_cmd_handler(shell);
	
}
