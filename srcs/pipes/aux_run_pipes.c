/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_run_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:45:59 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/12 09:03:04 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_outfile_and_next_cmd(t_cmd *pipe, int *next_pipe)
{
	if (pipe->outfile)
	{
		out_file_create(pipe->outfile);
		next_pipe[OUT] = out_file_open(pipe->outfile, pipe->write_mode);
	}
	else if (!pipe->next_cmd)
	{
		next_pipe[OUT] = out_file_open(pipe->outfile, pipe->write_mode);
	}
	if (pipe->next_cmd)
	{
		create_pipes(next_pipe);
	}
}

void	handle_infile(t_cmd *pipe, t_input cmd_input, int *prev_pipe)
{
	if (pipe->infile || cmd_input.head == pipe)
	{
		prev_pipe[IN] = in_file_open(pipe->infile, pipe->infile_mode);
	}
}

void	run_process_if(t_cmd *pipe, t_shell *shell, int *p_pipe,int *n_pipe)
{
	if (p_pipe[IN] >= 0)
		run_process(pipe->cmd_list, shell, p_pipe, n_pipe);
}
