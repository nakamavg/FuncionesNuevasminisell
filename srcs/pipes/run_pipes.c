/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:54:23 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/12 09:15:55 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_process(char **cmd, t_shell *shell, int pipe_in[2], int pipe_out[2])
{
	int	pid;

	pid = fork_process();
	if (pid == 0)
	{
		dup_and_close_fds(pipe_in, STDIN_FILENO);
		dup_and_close_fds(pipe_out, STDOUT_FILENO);
		exec_cmd(cmd, shell);
	}
	if (pipe_in[0] != IN)
	{
		close(pipe_in[0]);
		close(pipe_in[1]);
	}
	if (pipe_out[OUT] != STDOUT_FILENO)
		close(pipe_out[OUT]);
}

void	run_pipes(t_shell *shell, t_input cmd_input, t_cmd *pipe)
{
	int	status;
	int	prev_pipe[2];
	int	next_pipe[2];

	status = 0;
	pipe_fd(&prev_pipe[IN], &prev_pipe[OUT]);
	while (pipe)
	{
		pipe_fd(&next_pipe[IN], &next_pipe[OUT]);
		handle_outfile_and_next_cmd(pipe, next_pipe);
		handle_infile(pipe, cmd_input, prev_pipe);
		run_process_if(pipe, shell, prev_pipe, next_pipe);
		prev_pipe[IN] = next_pipe[IN];
		pipe = pipe->next_cmd;
	}
	close(prev_pipe[IN]);
	unlink("/tmp/here_doc");
	while (waitpid(-1, &status, 0) > 0)
		;
	g_status = set_g_status(status);
}
