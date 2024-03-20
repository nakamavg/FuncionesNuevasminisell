/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:11:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 17:24:35 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_pipe(const char *text, size_t text_length, int initial_idx)
{
	t_cmd *token;

	if (ft_strchr(" \t\n\v\f\r", *text) && text_length <= 1)
		return (NULL);
	token = malloc(sizeof(t_cmd));
	if (!token)
		return (NULL);
	token->text = ft_substr(text, initial_idx, text_length);
	token->infile = ft_infile_content(token->text);
	if (token->infile)
		token->infile_mode = ft_infile_mode(token->text);
	token->outfile = ft_outfile_content(token->text);
	if (token->outfile)
		token->write_mode = ft_outfile_mode(token->text);
	// TODO: Build a splitter that takes care of the strings
		// STEPS:
		//DONE  when doing the split, the string is a whole block itself
		//DONE if the "" string contains $, replace the content if available or use NULL
		token->cmd_list = cmd_split(token->text, token->infile, token->outfile);
		// token->cmd_list = expand_variable(cmd_split(token->text, token->infile, token->outfile));
		// char **tmp = token->cmd_list;
		// free(token->cmd_list);
		token->cmd_list = expand_variable(token->cmd_list);
		// token->cmd_list = expand_variable(token->cmd_list);
		// free(tmp);

		// If $ is not within a string, still expand it
		// Document about how to deal with the case $?
	
	// TODO: ASK: Do I have to deal with wrong flags? 
	token->next_cmd = NULL;
	token->prev_token = NULL;
	return (token);
}

void	add_pipe(t_input *cmd_list, t_cmd *new_token)
{
	t_cmd *tmp;

	if (!new_token)
		return ;
	if (!cmd_list->head)
	{
		cmd_list->head = new_token;
		cmd_list->token = cmd_list->head;
	}
	else
	{
		tmp = cmd_list->head;
		while (tmp->next_cmd)
			tmp = tmp->next_cmd;
		tmp->next_cmd = new_token;
		new_token->prev_token = tmp;
		new_token->prev_token->next_cmd = new_token;
	}
	printf("Added token: %s\n", new_token->text);
}
