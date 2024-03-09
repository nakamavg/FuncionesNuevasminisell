/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:18:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/09 17:01:28 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input *init_input()
{
	t_input *input_struct;

	input_struct = malloc(sizeof(t_input));
	if (!input_struct)
		return (NULL);
	input_struct->head = NULL;
	input_struct->token = NULL;
	return (input_struct);
}


static void add_token(t_input *input_struct, t_token *new_token)
{
	t_token *tmp;

	if (!new_token)
		return ;
	if (!input_struct->head)
	{
		input_struct->head = new_token;
		input_struct->token = input_struct->head;
	}
	else
	{
		tmp = input_struct->head;
		while (tmp->next_token)
			tmp = tmp->next_token;
		tmp->next_token = new_token;
		new_token->prev_token = tmp;
		new_token->prev_token->next_token = new_token;
	}
//	printf("Added token: %s\n", new_token->text);
}


static t_token *init_token(const char *text, size_t text_length, int initial_idx)
{
	t_token *token;

	if (ft_strchr(" \t\n\v\f\r", *text) && text_length <= 1)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_TYPE_UNKNOWN;
	token->text = ft_substr(text, 0, text_length);
	token->text = ft_substr(text, 0, text_length);
	token->text_length = text_length;
	token->initial_idx = initial_idx;
	token->exec_position = -1;
	token->next_token = NULL;
	token->prev_token = NULL;
	return (token);
}

static int ft_is_special_char(char c)
{
	return (ft_strchr("<>|;&\\$'\"`()*?!=", c) != NULL);
}

int	ft_isspace(int c)
{
	return (ft_strchr(" \t\n\v\f\r", c) != NULL);
}

static  size_t input_split(const char *input, t_input *input_struct, int initial_idx)
{
	size_t     cursor;

	cursor = 0;
	if (ft_is_special_char(input[cursor]))
	{
		if (input[cursor + 1] == input[cursor])
		{
			add_token(input_struct, init_token(&input[cursor], 2, initial_idx));
			return (2);
		}
		if (!ft_strncmp(&input[cursor], "$", 1))
		{
			while (input[cursor] && !ft_isspace(input[cursor]))
				cursor++;
			add_token(input_struct, init_token(input, cursor, initial_idx));
			return (cursor);
		}
		add_token(input_struct, init_token(&input[cursor], 1, initial_idx));
		return (1);
	}
	cursor = -1;
	while ((++cursor <= ft_strlen(input)) && (!ft_is_special_char(input[cursor])))
		;
	add_token(input_struct, init_token(input, cursor, initial_idx));
	return (cursor);
}

void token_type(t_token *token, int type)
{
	if (token->type == TOKEN_TYPE_UNKNOWN)
		token->type = type;
}

static int process_sentence(t_input *input, const char *delimiter, int type)
{
	int closed_sentence;

	closed_sentence = 0;
	token_type(input->token, type);
	input->token = input->token->next_token;
	while (input->token && ft_strncmp(input->token->text, delimiter, 1))
	{
		if (!ft_strncmp(input->token->text, "$", 1) && type == TOKEN_TYPE_DOUBLE_QUOTE)
			token_type(input->token, TOKEN_TYPE_EXPAND);
		else
			token_type(input->token, TOKEN_TYPE_STRING);
		input->token = input->token->next_token;
	}
	if (input->token && !ft_strncmp(input->token->text, delimiter, 1))
	{
		closed_sentence = !closed_sentence;
		token_type(input->token, type);
	}
	else
	{
		if (!closed_sentence)
		{
			printf("Error: Not closed string used as input\n");
			return (1);
		}
	}
	return (0);
}

int build_sentence(t_input *input)
{
	int	end;

	end = 0;
	input->token = input->head;
	while (input->token->next_token)
	{
		if (input->token && !ft_strncmp(input->token->text, "\"", 1))
			end = process_sentence(input, "\"", TOKEN_TYPE_DOUBLE_QUOTE);
		else if (input->token && !ft_strncmp(input->token->text, "'", 1))
			end = process_sentence(input, "'", TOKEN_TYPE_SINGLE_QUOTE);
		if (end)
			return (1); // TODO: This is because of an error. Deal with it to exit properly the program (wrong input, str not enclosed)
		input->token = input->token->next_token;
	}
	return (0);
}

int	in_redirections(t_token *token)
{
	if (ft_strlen(token->text) == 1)
	{
		token_type(token, TOKEN_TYPE_REDIR_IN);
		if (!token->next_token)
			return (printf("no in file to redirect"), 1);
		token_type(token->next_token, TOKEN_TYPE_IN_FILE);
	}
	else if (ft_strlen(token->text) == 2)
	{
		token_type(token, TOKEN_TYPE_REDIR_HEREDOC);
		if (!token->next_token)
			return (printf("no EOF for the here_doc file"), 1);
		token_type(token->next_token, TOKEN_TYPE_EOF);
	}
	return (0);
}

int	out_redirections(t_token *token)
{
	if (ft_strlen(token->text) == 1)
	{
		token_type(token, TOKEN_TYPE_REDIR_OUT);
		if (!token->next_token)
			return (printf("no out file to redirect"), 1);
		token_type(token->next_token, TOKEN_TYPE_IN_FILE);
	}
	else if (ft_strlen(token->text) == 2)
	{
		token_type(token, TOKEN_TYPE_REDIR_APPEND);
		if (!token->next_token)
			return (printf("no out file to append"), 1);
		token_type(token->next_token, TOKEN_TYPE_REDIR_OUT);
	}
	return (0);
}
// TODO: FIX
int	check_pipes(t_token *token)
{
	token_type(token, TOKEN_TYPE_PIPE);
	if (!token->prev_token)	
		return (printf("Missing program before the pipe\n"), 1);
	if (token->prev_token->type != TOKEN_TYPE_UNKNOWN && token->prev_token->type != TOKEN_TYPE_COMMAND)  // TODO: Potentially I have to improve this logic to deal with echo and other commands that receive an input with " "
	{
		if (token->prev_token->type != TOKEN_TYPE_DOUBLE_QUOTE && token->prev_token->type != TOKEN_TYPE_SINGLE_QUOTE)
			return (printf("The previous is not an executable: %s\n", token->prev_token->text));
	}
	if (!token->next_token)
		return (printf("Missing program after the pipe\n"), 1);
	if (token->next_token->type != TOKEN_TYPE_UNKNOWN) // TODO: Potentially I have to improve this logic to deal with echo and other commands that receive an input with " "
		return (printf("The next is not an executable"));
	// printf("++++++++\nPreview token: %s\nCurrent Token: %s\nNext token: %s\n=======\n", token->prev_token->text, token->text, token->next_token->text);
	token_type(token->prev_token, TOKEN_TYPE_COMMAND);
	token_type(token->next_token, TOKEN_TYPE_COMMAND);
	return (0);
}

int	build_metachars(t_input *input)
{
//	int err;
//
//	err = 0;
	input->token = input->head;
	while (input->token->next_token)
	{
		if	(input->token && !ft_strncmp(input->token->text, "<", 1))
			in_redirections(input->token);
		else if	(input->token && !ft_strncmp(input->token->text, ">", 1))
			out_redirections(input->token);
		else if	(input->token && !ft_strncmp(input->token->text, "|", 1))
			check_pipes(input->token);

		input->token = input->token->next_token;
	}
	return (0);
}


int input_sanitize(const char *input)
{
	int cursor;
	int next;

	cursor = -1;
	while (input[++cursor])
	{
		next = cursor + 1;
		while (ft_isspace(input[next]))
			next++;
		if (input[cursor] == '|' && ft_strchr("|<>", input[next]))
			return (printf("Error: | followed by %c\n", input[next]), 1);
	}
	return (0);
}

t_input   *lexer(const char *input)
{
	t_input *input_struct;
	int     cursor;
//	int     input_length;
	int		err;

	printf("input: %s\n\n", input);
	if (input_sanitize(input))
		return (printf("non-valid input\n"), NULL);
	printf("input sanitized\n");
	input_struct = init_input();
	if (!input_struct)
		return (NULL);
//	input_length = ft_strlen(input);
	input = ft_strtrim(input, " \t\n\v\f\r");
	cursor = 0;
	while (input[cursor])
		cursor += input_split(input + cursor, input_struct, cursor);
	err = build_sentence(input_struct);
	if (err)
		return (printf("string error"), input_struct);
	build_metachars(input_struct);






	    const char *token_type_names[] = {
        "TOKEN_TYPE_UNKNOWN",
        "TOKEN_TYPE_REDIR_IN",
        "TOKEN_TYPE_REDIR_OUT",
        "TOKEN_TYPE_REDIR_APPEND",
        "TOKEN_TYPE_REDIR_HEREDOC",
        "TOKEN_TYPE_PIPE",
        "TOKEN_TYPE_EOF",
        "TOKEN_TYPE_COMMAND",
        "TOKEN_TYPE_IN_FILE",
        "TOKEN_TYPE_OUT_FILE",
        "TOKEN_TYPE_EQUALS",
        "TOKEN_TYPE_EXCLAMATION",
        "TOKEN_TYPE_AMPERSAND",
        "TOKEN_TYPE_WILDCARD",
        "TOKEN_TYPE_BACKTICK",
        "TOKEN_TYPE_SEMICOLON",
        "TOKEN_TYPE_BACKSLASH",
        "TOKEN_TYPE_DOLLAR",
        "TOKEN_TYPE_DOT",
        "TOKEN_TYPE_QUESTION",
        "TOKEN_TYPE_SINGLE_QUOTE",
        "TOKEN_TYPE_DOUBLE_QUOTE",
        "TOKEN_TYPE_OPEN_PARENTHESIS",
        "TOKEN_TYPE_CLOSE_PARENTHESIS",
        "TOKEN_TYPE_STRING",
        "TOKEN_TYPE_VAR",
        "TOKEN_TYPE_EXPAND"
    };
	input_struct->token = input_struct->head;
	while (input_struct->token)
	{
		printf("Token: %s\n\ttext_len: %lu\n\ttype: %s\n", input_struct->token->text, input_struct->token->text_length, token_type_names[input_struct->token->type]);
		input_struct->token = input_struct->token->next_token;
	}
	printf("Head: %s\n", input_struct->head->text);
    // for (int i = 0; i < TOKEN_TYPE_MAX; i++) {
    //     printf("%s is %d\n", token_type_names[i], i);
    // }
	return (input_struct);
}

