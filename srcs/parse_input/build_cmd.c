/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:34 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 17:10:01 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initializes the input structure.
 * 
 * @return The initialized input structure.
 */
t_input	init_input()
{
	t_input cmd_list;

	cmd_list.head = NULL;
	cmd_list.token = NULL;
	return (cmd_list);
}

/**
 * Builds the command list where each node is a pipe.
 * 
 * @param input The input string to parse.
 * @param cmd_list The pointer to the input structure to store the command list.
 */
void	build_cmdlst(const char *input, t_input *cmd_list)
{
	int idx;
	int len;
	int pipe_idx;

	idx = 0;
	len = ft_strlen(input);
	while (input[idx])
	{
		while (ft_isspace(input[idx]))
			idx++;
		if (input[idx] == '"')
			while (input[idx] && input[++idx] != '"')
				;
		if (input[idx] == '\'')
			while (input[idx] && input[++idx] != '\'')
				;
		if (input[idx] && (input[idx] == '|' || idx == len - 1))
		{
			if (input[idx] != '|')
				idx++;
			add_pipe(cmd_list, init_pipe(input, idx - pipe_idx, pipe_idx));
			while (ft_isspace(input[++idx]))
				;
			pipe_idx = idx;
		}
		idx++;
	}
}

/**
 * Cleans up the allocated space in the command list.
 * 
 * @param cmd_list The pointer to the input structure containing the command list.
 */
void cleanup_cmd_list(t_input *cmd_list)
{
	t_cmd *current_token = cmd_list->head;
	t_cmd *next_token;
	char **original_cmd_list;

	while (current_token)
	{
		next_token = current_token->next_cmd;
		if (current_token->text)
			free(current_token->text);
		if (current_token->infile)
			free(current_token->infile);
		if (current_token->outfile)
			free(current_token->outfile);
		original_cmd_list = current_token->cmd_list;
		while (*current_token->cmd_list)
		{
			if (*current_token->cmd_list)
				free(*current_token->cmd_list);
			current_token->cmd_list++;
		}
		free(original_cmd_list);
		free(current_token);
		current_token = next_token;
	}
	free(current_token);
}