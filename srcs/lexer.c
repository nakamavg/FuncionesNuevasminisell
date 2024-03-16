/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:41:40 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 02:19:03y alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:41:40 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 00:52:45by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:18:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/14 11:22:38 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static  size_t input_split(const char *input, t_input *cmd_list, int initial_idx)
//{
//	size_t     cursor;
//
//	cursor = 0;
//	if (ft_is_special_char(input[cursor]))
//	{
//		if (!ft_strncmp(&input[cursor], "$", 1))
//		{
//			while (input[cursor] && !ft_isspace(input[cursor]))
//				cursor++;
//			add_pipe(cmd_list, init_pipe(input, cursor, initial_idx));
//			return (cursor);
//		}
//		if (!ft_strncmp(&input[cursor], "<", 1)) // Check for '<'
//		{
//			if (!ft_strncmp(&input[cursor + 1], "<", 1)) // Check for '<'
//			{
//				add_pipe(cmd_list, init_pipe(&input[cursor], 2, initial_idx));
//				cursor++;
//			}
//			else
//				add_pipe(cmd_list, init_pipe(&input[cursor], 1, initial_idx));
//
//			cursor++;
//			while (input[cursor] && ft_isspace(input[cursor])) // Skip any whitespace after the '<'
//				cursor++;
//			size_t start = cursor;
//			while (input[cursor] && !ft_isspace(input[cursor]) && !ft_is_special_char(input[cursor])) // advance till the end of the word
//				cursor++;
//			add_pipe(cmd_list, init_pipe(&input[start], cursor - start, initial_idx + start));
//			return (cursor);
//		}
//		if (!ft_strncmp(&input[cursor], ">", 1)) // Check for '>'
//		{
//			if (!ft_strncmp(&input[cursor + 1], ">", 1)) // Check for '>'
//			{
//				add_pipe(cmd_list, init_pipe(&input[cursor], 2, initial_idx));
//				cursor++;
//			}
//			else
//				add_pipe(cmd_list, init_pipe(&input[cursor], 1, initial_idx));
//
//			cursor++;
//			while (input[cursor] && ft_isspace(input[cursor])) // Skip any whitespace after the '<'
//				cursor++;
//			size_t start = cursor;
//			while (input[cursor] && !ft_isspace(input[cursor]) && !ft_is_special_char(input[cursor])) // advance till the end of the word
//				cursor++;
//			add_pipe(cmd_list, init_pipe(&input[start], cursor - start, initial_idx + start));
//			return (cursor);
//		}
//		add_pipe(cmd_list, init_pipe(&input[cursor], 1, initial_idx));
//		return (1);
//	}
//	cursor = -1;
//	while ((++cursor <= ft_strlen(input)) && (!ft_is_special_char(input[cursor])))
//		;
//	add_pipe(cmd_list, init_pipe(input, cursor, initial_idx));
//	return (cursor);
//}


//static int process_sentence(t_input *input, const char *delimiter, int type)
//{
//	int closed_sentence;
//
//	closed_sentence = 0;
//	token_type(input->token, type);
//	input->token = input->token->next_cmd;
//	while (input->token && ft_strncmp(input->token->text, delimiter, 1))
//	{
//		if (!ft_strncmp(input->token->text, "$", 1) && type == TOKEN_TYPE_DOUBLE_QUOTE)
//			token_type(input->token, TOKEN_TYPE_EXPAND);
//		else
//			token_type(input->token, TOKEN_TYPE_STRING);
//		input->token = input->token->next_cmd;
//	}
//	if (input->token && !ft_strncmp(input->token->text, delimiter, 1))
//	{
//		closed_sentence = !closed_sentence;
//		token_type(input->token, type);
//	}
//	else
//	{
//		if (!closed_sentence)
//		{
//			printf("Error: Not closed string used as input\n");
//			return (1);
//		}
//	}
//	return (0);
//}

//int build_sentence(t_input *input)
//{
//	int	end;
//
//	end = 0;
//	input->token = input->head;
//	while (input->token->next_cmd)
//	{
//		if (input->token && !ft_strncmp(input->token->text, "\"", 1))
//			end = process_sentence(input, "\"", TOKEN_TYPE_DOUBLE_QUOTE);
//		else if (input->token && !ft_strncmp(input->token->text, "'", 1))
//			end = process_sentence(input, "'", TOKEN_TYPE_SINGLE_QUOTE);
//		if (end)
//			return (1); // TODO: This is because of an error. Deal with it to exit properly the program (wrong input, str not enclosed)
//		input->token = input->token->next_cmd;
//	}
//	return (0);
//}
//
//int	in_redirections(t_cmd *token)
//{
//	if (ft_strlen(token->text) == 1)
//	{
//		token_type(token, TOKEN_TYPE_REDIR_IN);
//		if (!token->next_cmd)
//			return (printf("no in file to redirect"), 1);
//		token_type(token->next_cmd, TOKEN_TYPE_IN_FILE);
//	}
//	else if (ft_strlen(token->text) == 2)
//	{
//		token_type(token, TOKEN_TYPE_REDIR_HEREDOC);
//		if (!token->next_cmd)
//			return (printf("no EOF for the here_doc file"), 1);
//		token_type(token->next_cmd, TOKEN_TYPE_EOF);
//	}
//	return (0);
//}
//
//int	out_redirections(t_cmd *token)
//{
//	if (ft_strlen(token->text) == 1)
//	{
//		token_type(token, TOKEN_TYPE_REDIR_OUT);
//		if (!token->next_cmd)
//			return (printf("no out file to redirect"), 1);
//		token_type(token->next_cmd, TOKEN_TYPE_OUT_FILE);
//	}
//	else if (ft_strlen(token->text) == 2)
//	{
//		token_type(token, TOKEN_TYPE_REDIR_APPEND);
//		if (!token->next_cmd)
//			return (printf("no out file to append"), 1);
//		token_type(token->next_cmd, TOKEN_TYPE_OUT_FILE);
//	}
//	return (0);
//}
//
//int	check_pipes(t_cmd *token)
//{
//	token_type(token, TOKEN_TYPE_PIPE);
//	if (!token->prev_token)
//		return (printf("Missing program before the pipe\n"), 1);
////	if (token->prev_token->type != TOKEN_TYPE_UNKNOWN && token->prev_token->type != TOKEN_TYPE_COMMAND)
////	{
////		if (token->prev_token->type != TOKEN_TYPE_DOUBLE_QUOTE && token->prev_token->type != TOKEN_TYPE_SINGLE_QUOTE)
////			return (printf("The previous is not an executable: %s\n", token->prev_token->text));
////	}
//	if (!token->next_cmd)
//		return (printf("Missing program after the pipe\n"), 1);
//	if (token->next_cmd->type != TOKEN_TYPE_UNKNOWN)
//		return (printf("The next is not an executable"), 1);
//	// printf("++++++++\nPreview token: %s\nCurrent Token: %s\nNext token: %s\n=======\n", token->prev_token->text, token->text, token->next_cmd->text);
//	token_type(token->prev_token, TOKEN_TYPE_COMMAND);
//	token_type(token->next_cmd, TOKEN_TYPE_COMMAND);
//	return (0);
//}
//
//int	build_metachars(t_input *input)
//{
//	int err;
////
//	err = 0;
//	input->token = input->head;
//	while (input->token->next_cmd && !err)
//	{
//		if	(input->token && !ft_strncmp(input->token->text, "<", 1))
//			err = in_redirections(input->token);
//		else if	(input->token && !ft_strncmp(input->token->text, ">", 1))
//			err = out_redirections(input->token);
//		else if	(input->token && !ft_strncmp(input->token->text, "|", 1))
//			err = check_pipes(input->token);
//
//		input->token = input->token->next_cmd;
//	}
//	return (err);
//}


//int input_sanitize(const char *input)
//{
//	int cursor;
//	int next;
//
//	cursor = -1;
//	while (input[++cursor])
//	{
//		next = cursor + 1;
//		while (ft_isspace(input[next]))
//			next++;
////		if (input[cursor] == '|' && ft_strchr("|<>", input[next]))
////			return (printf("Error: | followed by %c\n", input[next]), 1);
//	}
//	return (0);
//}

//t_input   *lexer(const char *input)
//{
//	t_input *cmd_list;
//	int     cursor;
//	int		err;
//
//	printf("input: %s\n\n", input);
//	if (input_sanitize(input))
//		return (printf("non-valid input\n"), NULL);
//	printf("input sanitized\n");
//	cmd_list = init_input();
//	if (!cmd_list)
//		return (NULL);
//	input = ft_strtrim(input, " \t\n\v\f\r");
//	cursor = 0;
//	while (input[cursor])
//		cursor += input_split(input + cursor, cmd_list, cursor);
//	err = build_sentence(cmd_list);
//	if (err)
//		return (printf("string error\n"), cleanup_cmd_list(cmd_list), NULL);
//	if (build_metachars(cmd_list))
//		return (printf("metachars error\n"), cleanup_cmd_list(cmd_list), NULL);
//	test_lexer(cmd_list);
//	return (cmd_list);
//}




//++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++

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
		// when doing the split, the string is a whole block itself
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
	cmd_list->token = cmd_list->head;
	while (cmd_list->token)
	{
		if (cmd_list->token->text)
			free(cmd_list->token->text);
		free(cmd_list->token);
		cmd_list->token = cmd_list->token->next_cmd;
	}
	// free(cmd_list);
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
