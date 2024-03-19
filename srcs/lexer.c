/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:41:40 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/18 22:59:20by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	return (ft_strchr(" \t\n\v\f\r", c) != NULL);
}


static t_input init_input()
{
	t_input cmd_list;

//	cmd_list = malloc(sizeof(t_input));
//	if (!cmd_list)
//		return (NULL);
	cmd_list.head = NULL;
	cmd_list.token = NULL;
	return (cmd_list);
}
//
//
static void add_pipe(t_input *cmd_list, t_cmd *new_token)
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

static	Token_Type ft_infile_mode(const char *input)
{
	while(ft_isspace(*input))
		input++;
	if (!input)
		return (TOKEN_TYPE_UNKNOWN);
	if (*input == '<')
	{
		if (*input++ == '<')
			return (TOKEN_TYPE_REDIR_HEREDOC);
		return (TOKEN_TYPE_REDIR_IN);
	}
	return (TOKEN_TYPE_UNKNOWN);
}

static	char *ft_infile_content(const char *input)
{
	size_t len;

	while (*input && ft_isspace(*input))
		input++;
	if (!input)
		return (NULL);
	if (*input == '<')
	{
		input++;
		if (*input == '<')
			input++;
	}
	else
		return (NULL);
	while (*input && ft_isspace(*input))
		input++;
	len = 0;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	return (ft_substr(input, 0, len));
	
}

static	Token_Type ft_outfile_mode(const char *input)
{
	while (*input && *input != '>')
		input++;
	if (!input)
		return (TOKEN_TYPE_UNKNOWN);
	if (*input == '>')
	{
		if (*input++ == '>')
			return (TOKEN_TYPE_REDIR_APPEND);
		return (TOKEN_TYPE_REDIR_OUT);
	}
	return (TOKEN_TYPE_UNKNOWN);
}

static	char *ft_outfile_content(const char *input)
{
	size_t len;

	while (*input && *input != '>')
		input++;
	if (!input)
		return (NULL);
	if (*input == '>')
	{
		input++;
		if (*input == '>')
			input++;
	}
	else
		return (NULL);
	while (*input && ft_isspace(*input))
		input++;
	len = 0;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	return (ft_substr(input, 0, len));
	
}

char **cmd_split(const char *text, char *in, char *out)
{
	char **cmd_list;
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	cmd_list = ft_split_cmd(text);
	while (cmd_list[i])
	{
		tmp = ft_strtrim(cmd_list[i++], " \t\n\v\f\r");
		if (ft_strncmp(tmp, in, ft_strlen(tmp)) && ft_strncmp(tmp, out, ft_strlen(tmp)) && *tmp != '<' && *tmp != '>')
		{
			free(cmd_list[j]);
			cmd_list[j++] = ft_strdup(tmp);
			free(tmp);
		}
		else
			free(tmp);
	}
	cmd_list[j] = NULL;
	while (j < i)
	{
		free(cmd_list[j]);
		j++;
	}
	return (cmd_list);
}


static t_cmd *init_pipe(const char *text, size_t text_length, int initial_idx)
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
	token->cmd_list = cmd_split(token->text, token->infile, token->outfile);
		// if the "" string contains $, replace the content if available or use NULL
		// If $ is not within a string, still expand it
		// Document about how to deal with the case $?
	
	// TODO: ASK: Do I have to deal with wrong flags? 
	token->next_cmd = NULL;
	token->prev_token = NULL;
	return (token);
}

void cleanup_cmd_list(t_input *cmd_list)
{
    t_cmd *current_token = cmd_list->head;
    t_cmd *next_token;
	char	*tmp_cmd;

    while (current_token)
    {
        next_token = current_token->next_cmd;
        if (current_token->text)
            free(current_token->text);
		if (current_token->infile)
			free(current_token->infile);
		if (current_token->outfile)
			free(current_token->outfile);
		while (*current_token->cmd_list)
		{
			tmp_cmd = *(current_token->cmd_list++);	
			free(current_token->cmd_list);
			current_token->cmd_list = &tmp_cmd;
		}
        free(current_token);
        current_token = next_token;
    }
	free(current_token);
}

int sanitize_input(const char *input)
{
	int within_dq_sentence = 0;
	int within_sq_sentence = 0;
	int cursor = 0;

	while (*input)
	{
		if (*input == '\"' && !within_sq_sentence)
			within_dq_sentence = !within_dq_sentence;
		if (*input == '\'' && !within_dq_sentence)
			within_sq_sentence = !within_sq_sentence;
		if (*input == '|' && !within_dq_sentence && !within_sq_sentence)
		{
			while (ft_isspace(input[++cursor]))
				;
			if (input[cursor] == '|')
				return (printf("Error: two pipes without commands in between\n"), 1);
			cursor = 0;
		}
		input++;
	}
	if (within_sq_sentence || within_dq_sentence)
		return (printf("Error: Not closed string used as input\n"), 1);
	return (printf("input sanitized\n"), 0);
}

void build_cmdlst(const char *input, t_input (*cmd_list))
{
	int idx;
	int	len;
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

t_input   lexer(const char *input)
{
	t_input cmd_list;

	cmd_list = init_input();
	printf("input: %s\n", input);
	if (sanitize_input(input))
		return (printf("non-valid input\n"), cmd_list);
	build_cmdlst(input, &cmd_list);
	test_lexer(&cmd_list);

	return (cmd_list);
}
