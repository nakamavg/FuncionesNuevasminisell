/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:34 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/03 18:22:38 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initializes the input structure.
 * 
 * @return The initialized input structure.
 */
t_input	init_input(void)
{
	t_input	cmd_list;

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
// void	build_cmdlst(const char *input, t_input *cmd_list)
// {
// 	int	idx;
// 	int	pipe_idx;

// 	idx = -1;
// 	while (input[++idx])
// 	{
// 		while (ft_isspace(input[idx]))
// 			idx++;
// 		if (input[idx] == '"')
// 			while (input[idx] && input[++idx] != '"')
// 				;
// 		if (input[idx] == '\'')
// 			while (input[idx] && input[++idx] != '\'')
// 				;
// 		if (input[idx] && (input[idx] == '|'
// 				|| idx == (int)ft_strlen(input) - 1))
// 		{
// 			if (input[idx] != '|')
// 				idx++;
// 			add_pipe(cmd_list, init_pipe(input, idx - pipe_idx, pipe_idx));
// 			while (ft_isspace(input[++idx]))
// 				;
// 			pipe_idx = idx;
// 		}
// 	}
// }
void	build_cmdlst(const char *in, t_shell *shell)
{
	int	idx;
	int	pipe_idx;

	idx = -1;
	char *input = ft_strtrim(in, " \t\n\v\f\r");
	while (input[++idx])
	{
		while (input[idx] && ft_isspace(input[idx]))
			idx++;
		if (input[idx] == '"')
			while (input[idx] && input[++idx] != '"')
				;
		if (input[idx] == '\'')
			while (input[idx] && input[++idx] != '\'')
				;
		if (input[idx] && (input[idx] == '|'
				|| idx == (int)ft_strlen(input) - 1))
		{
			if (input[idx] != '|')
				idx++;
			add_pipe(&shell->parsed_input, init_pipe(input, idx - pipe_idx, pipe_idx, shell));
			if (!input[idx])
				break ;
			while (ft_isspace(input[++idx]))
				;
			pipe_idx = idx;
		}
	}
	free(input);
}

/**
 * Cleans up the allocated space in the command list.
 * 
 * @param cmd_list The pointer to the input structure containing
 * the command list.
 */
void	cleanup_cmd_list(t_input *cmd_list)
{
	t_cmd	*current_token;
	t_cmd	*next_token;
	char	**original_cmd_list;

	current_token = cmd_list->head;
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
			free(*current_token->cmd_list++);
		free(original_cmd_list);
		free(current_token);
		current_token = next_token;
	}
	free(current_token);
}
