/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 00:34:49 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/27 00:50:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		unix_error("pipe error", NULL);
}

void	dup_and_close_fds(int pipe_fd[2], int std_fd)
{
	if (pipe_fd[std_fd] != std_fd)
	{
		dup2(pipe_fd[std_fd], std_fd);
		close(pipe_fd[IN]);
		close(pipe_fd[OUT]);
	}
}

void	set_null_pipe(int *in, int *out)
{
	*in = -1;
	*out = -1;
}

int	set_global_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (EXIT_FAILURE);
}
