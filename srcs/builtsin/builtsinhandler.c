/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtsinhandler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:06:34 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/03/10 14:12:55 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void more_cmd_handler(t_shell *shell)
{
	if(ft_strncmp(shell->input,"$USER", 5) == 0)
	return((void)printf("%s", shell->user));
	else if(ft_strncmp(shell->input,"$PATH", 5) == 0)
	return((void)printf("%s", shell->env));
	else if(ft_strncmp(shell->input,"$HOME", 5) == 0)
	return((void)printf("%s", shell->home));
	else
		ft_putstr_fd("command not found \n", STDOUT_FILENO);
}

void command_handler(t_shell *shell)
{
	if (ft_strncmp(shell->input, "exit", 4) == 0)
		return(exit(0));
	else if (ft_strncmp(shell->input, "cd", 2) == 0)
			return(cd(shell));
	else if (ft_strncmp(shell->input, "pwd", 3) == 0)
		return((void)printf("%s\n", getcwd(NULL, 0)));
	else if (ft_strncmp(shell->input, "export", 6) == 0)
		return(export(shell)); 
	else if (ft_strncmp(shell->input, "unset ", 6) == 0)
		return(unset(shell)); 
	else if (ft_strncmp(shell->input, "env", 3) == 0)
		ft_putstr_fd("env \n", STDOUT_FILENO);
	else if (ft_strncmp(shell->input, "echo", 4) == 0)
		printf("%s\n", shell->input + 5);
	more_cmd_handler(shell);
	
}
