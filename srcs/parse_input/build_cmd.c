/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:34 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/11 09:39:52 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	init_input(void)
{
	t_input	cmd_list;

	cmd_list.head = NULL;
	cmd_list.token = NULL;
	return (cmd_list);
}

static int	advance_quotes(const char *input, int idx)
{
	if (input[idx] == '"')
		while (input[idx] && input[++idx] != '"')
			;
	if (input[idx] == '\'')
		while (input[idx] && input[++idx] != '\'')
			;
	return (idx);
}

void	build_cmdlst(const char *input, t_shell *shell)
{
	int		idx;
	int		pipe_idx;

	idx = -1;
	pipe_idx = 0;
	while (input[++idx])
	{
		while (input[idx] && ft_isspace(input[idx]))
			idx++;
		idx = advance_quotes(input, idx);
		if (input[idx] && (input[idx] == '|' || idx == (int)ft_strlen(input)
				- 1))
		{
			if (input[idx] != '|')
				idx++;
			add_pipe(&shell->parsed_input, init_pipe(input, idx - pipe_idx,
					pipe_idx, shell));
			if (!input[idx])
				break ;
			while (ft_isspace(input[++idx]))
				;
			pipe_idx = idx;
		}
	}
}

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
		if (original_cmd_list)
			free(original_cmd_list);
		free(current_token);
		current_token = next_token;
	}
	if (current_token)
		free(current_token);
}
