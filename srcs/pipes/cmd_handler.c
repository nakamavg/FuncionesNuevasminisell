/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:07:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/12 10:23:01 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 04:06:34 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/11 09:37:51 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_Builtin	ft_is_builtin(char *cmd)
{
	if (check_names(cmd, "echo"))
		return (ECH0);
	if (check_names(cmd, "env"))
		return (ENV);
	if (check_names(cmd, "exit"))
		return (EXIT);
	if (check_names(cmd, "pwd"))
		return (PWD);
	if (check_names(cmd, "cd"))
		return (CD);
	if (check_names(cmd, "export"))
		return (EXPORT);
	if (check_names(cmd, "unset"))
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
		status = exit_shell(shell, shell->parsed_input.head->cmd_list);
	if (builtin == PWD)
		pwd();
	if (builtin == CD)
		status = cd(shell, cmd);
	if (builtin == EXPORT)
		status = export(shell, cmd);
	if (builtin == UNSET)
		unset(shell, shell->parsed_input.head->cmd_list);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	return (close(stdin_copy), close(stdout_copy), status);
}

int	run_builtin(t_shell *shell, char **cmd)
{
	if (check_names(cmd[0], "echo"))
		return (echo(cmd), 1);
	if (check_names(cmd[0], "env"))
		return (print_env(shell->env_list), 1);
	if (check_names(cmd[0], "exit"))
		return (exit_shell(shell, cmd), 1);
	if (check_names(cmd[0], "pwd"))
		return ((void)printf("%s\n", getcwd(NULL, 0)), 1);
	if (check_names(cmd[0], "cd"))
		return (cd(shell, cmd), 1);
	if (check_names(cmd[0], "export"))
		return (export(shell, cmd), 1);
	if (check_names(cmd[0], "unset"))
		return (unset(shell, cmd), 1);
	return (0);
}

void	command_handler(t_shell *shell)
{
	if (!shell->parsed_input.head->next_cmd
		&& ft_is_builtin(shell->parsed_input.head->cmd_list[0]) != NONE)
	{
		g_status = run_single_builtin(shell,
				shell->parsed_input.head->cmd_list);
		return ;
	}
	run_pipes(shell, shell->parsed_input, shell->parsed_input.head);
}
