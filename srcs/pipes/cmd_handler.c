/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:06:34 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/03 15:39:06 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_Builtin	ft_is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ECH0);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ENV);
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (EXIT);
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (PWD);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (CD);
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (EXPORT);
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (UNSET);
	return (NONE);
}

static void	handle_io_redirection(t_shell *shell, int *stdin_copy,
			int *stdout_copy)
{
	int	infile;
	int	outfile;

	*stdin_copy = dup(STDIN_FILENO);
	*stdout_copy = dup(STDOUT_FILENO);
	if (shell->parsed_input.head->infile)
	{
		infile = in_file_open(shell->parsed_input.head->infile,
				shell->parsed_input.head->infile_mode);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (shell->parsed_input.head->outfile)
	{
		out_file_create(shell->parsed_input.head->outfile);
		outfile = out_file_open(shell->parsed_input.head->outfile,
				shell->parsed_input.head->write_mode);
		dup2(outfile, STDOUT_FILENO);
	}
}

// static int	run_single_builtin(t_shell *shell)
// {
// 	t_Builtin	builtin;
// 	int			stdin_copy;
// 	int			stdout_copy;
// 	int			status;

// 	status = 0;
// 	builtin = ft_is_builtin(shell->parsed_input.head->cmd_list[0]);
// 	handle_io_redirection(shell, &stdin_copy, &stdout_copy);
// 	if (builtin == ECH0)
// 		echo(shell->parsed_input.head->cmd_list);
// 	if (builtin == ENV)
// 		print_env(shell->env_list);
// 	if (builtin == EXIT)
// 		status = exit_shell(shell,shell->parsed_input.head->cmd_list);
// 	if (builtin == PWD)
// 		printf("%s\n", getcwd(NULL, 0));
// 	if (builtin == CD)
// 		cd(shell);
// 	if (builtin == EXPORT)
// 		export(shell);
// 	if (builtin == UNSET)
// 		unset(shell);
// 	dup2(stdin_copy, STDIN_FILENO);
// 	dup2(stdout_copy, STDOUT_FILENO);
// 	return (close(stdin_copy), close(stdout_copy), status);
// }
static int	run_single_builtin(t_shell *shell, char **cmd)
{
	t_Builtin	builtin;
	int			stdin_copy;
	int			stdout_copy;
	int			status;

	status = 0;
	builtin = ft_is_builtin(shell->parsed_input.head->cmd_list[0]);
	handle_io_redirection(shell, &stdin_copy, &stdout_copy);
	if (builtin == ECH0)
		echo(shell->parsed_input.head->cmd_list);
	if (builtin == ENV)
		print_env(shell->env_list);
	if (builtin == EXIT)
		status = exit_shell(shell,shell->parsed_input.head->cmd_list);
	if (builtin == PWD)
		printf("%s\n", getcwd(NULL, 0));
	if (builtin == CD)
		cd(shell, cmd);
	if (builtin == EXPORT)
		export(shell);
	if (builtin == UNSET)
		unset(shell);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	return (close(stdin_copy), close(stdout_copy), status);
}

int	run_builtin(t_shell *shell)
{
	char	*cmd;

	cmd = shell->parsed_input.head->cmd_list[0];
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (echo(shell->parsed_input.head->cmd_list), 1);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (print_env(shell->env_list), 1);
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (exit_shell(shell, shell->parsed_input.head->cmd_list), 1);
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return ((void)printf("%s\n", getcwd(NULL, 0)), 1);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (cd(shell, shell->parsed_input.head->cmd_list), 1);
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (export(shell), 1);
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (unset(shell), 1);
	return (0);
}

void	command_handler(t_shell *shell)
{
	// if (!shell->parsed_input.head->next_cmd && run_single_builtin(shell))
	if (!shell->parsed_input.head->next_cmd &&
		ft_is_builtin(shell->parsed_input.head->cmd_list[0]) != NONE)
	{
		global_status = run_single_builtin(shell, shell->parsed_input.head->cmd_list);
		return ;
	}
	run_pipes(shell, shell->parsed_input, shell->parsed_input.head);
}
