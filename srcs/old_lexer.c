/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:18:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 01:31:44 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input *init_input()
{
	t_input *cmd_list;

	cmd_list = malloc(sizeof(t_input));
	if (!cmd_list)
		return (NULL);
	cmd_list->head = NULL;
	cmd_list->token = NULL;
	return (cmd_list);
}


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


static t_cmd *init_pipe(const char *text, size_t text_length, int initial_idx)
{
	t_cmd *token;

	if (ft_strchr(" \t\n\v\f\r", *text) && text_length <= 1)
		return (NULL);
	token = malloc(sizeof(t_cmd));
	if (!token)
		return (NULL);
	token->type = TOKEN_TYPE_UNKNOWN;
//	token->text = ft_substr(text, 0, text_length);
	token->text = ft_substr(text, 0, text_length);
	token->text_length = text_length;
	token->initial_idx = initial_idx;
	token->exec_position = -1;
	token->next_cmd = NULL;
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

static  size_t input_split(const char *input, t_input *cmd_list, int initial_idx)
{
	size_t     cursor;

	cursor = 0;
	if (ft_is_special_char(input[cursor]))
	{
		if (!ft_strncmp(&input[cursor], "$", 1))
		{
			while (input[cursor] && !ft_isspace(input[cursor]))
				cursor++;
			add_pipe(cmd_list, init_pipe(input, cursor, initial_idx));
			return (cursor);
		}
		if (!ft_strncmp(&input[cursor], "<", 1)) // Check for '<'
		{
			if (!ft_strncmp(&input[cursor + 1], "<", 1)) // Check for '<'
			{
				add_pipe(cmd_list, init_pipe(&input[cursor], 2, initial_idx));
				cursor++;
			}
			else
				add_pipe(cmd_list, init_pipe(&input[cursor], 1, initial_idx));

			cursor++;
			while (input[cursor] && ft_isspace(input[cursor])) // Skip any whitespace after the '<'
				cursor++;
			size_t start = cursor;
			while (input[cursor] && !ft_isspace(input[cursor]) && !ft_is_special_char(input[cursor])) // advance till the end of the word
				cursor++;
			add_pipe(cmd_list, init_pipe(&input[start], cursor - start, initial_idx + start));
			return (cursor);
		}
		if (!ft_strncmp(&input[cursor], ">", 1)) // Check for '>'
		{
			if (!ft_strncmp(&input[cursor + 1], ">", 1)) // Check for '>'
			{
				add_pipe(cmd_list, init_pipe(&input[cursor], 2, initial_idx));
				cursor++;
			}
			else
				add_pipe(cmd_list, init_pipe(&input[cursor], 1, initial_idx));

			cursor++;
			while (input[cursor] && ft_isspace(input[cursor])) // Skip any whitespace after the '<'
				cursor++;
			size_t start = cursor;
			while (input[cursor] && !ft_isspace(input[cursor]) && !ft_is_special_char(input[cursor])) // advance till the end of the word
				cursor++;
			add_pipe(cmd_list, init_pipe(&input[start], cursor - start, initial_idx + start));
			return (cursor);
		}
		add_pipe(cmd_list, init_pipe(&input[cursor], 1, initial_idx));
		return (1);
	}
	cursor = -1;
	while ((++cursor <= ft_strlen(input)) && (!ft_is_special_char(input[cursor])))
		;
	add_pipe(cmd_list, init_pipe(input, cursor, initial_idx));
	return (cursor);
}

void token_type(t_cmd *token, int type)
{
	if (token->type == TOKEN_TYPE_UNKNOWN)
		token->type = type;
}

static int process_sentence(t_input *input, const char *delimiter, int type)
{
	int closed_sentence;

	closed_sentence = 0;
	token_type(input->token, type);
	input->token = input->token->next_cmd;
	while (input->token && ft_strncmp(input->token->text, delimiter, 1))
	{
		if (!ft_strncmp(input->token->text, "$", 1) && type == TOKEN_TYPE_DOUBLE_QUOTE)
			token_type(input->token, TOKEN_TYPE_EXPAND);
		else
			token_type(input->token, TOKEN_TYPE_STRING);
		input->token = input->token->next_cmd;
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
	while (input->token->next_cmd)
	{
		if (input->token && !ft_strncmp(input->token->text, "\"", 1))
			end = process_sentence(input, "\"", TOKEN_TYPE_DOUBLE_QUOTE);
		else if (input->token && !ft_strncmp(input->token->text, "'", 1))
			end = process_sentence(input, "'", TOKEN_TYPE_SINGLE_QUOTE);
		if (end)
			return (1); // TODO: This is because of an error. Deal with it to exit properly the program (wrong input, str not enclosed)
		input->token = input->token->next_cmd;
	}
	return (0);
}

int	in_redirections(t_cmd *token)
{
	if (ft_strlen(token->text) == 1)
	{
		token_type(token, TOKEN_TYPE_REDIR_IN);
		if (!token->next_cmd)
			return (printf("no in file to redirect"), 1);
		token_type(token->next_cmd, TOKEN_TYPE_IN_FILE);
	}
	else if (ft_strlen(token->text) == 2)
	{
		token_type(token, TOKEN_TYPE_REDIR_HEREDOC);
		if (!token->next_cmd)
			return (printf("no EOF for the here_doc file"), 1);
		token_type(token->next_cmd, TOKEN_TYPE_EOF);
	}
	return (0);
}

int	out_redirections(t_cmd *token)
{
	if (ft_strlen(token->text) == 1)
	{
		token_type(token, TOKEN_TYPE_REDIR_OUT);
		if (!token->next_cmd)
			return (printf("no out file to redirect"), 1);
		token_type(token->next_cmd, TOKEN_TYPE_OUT_FILE);
	}
	else if (ft_strlen(token->text) == 2)
	{
		token_type(token, TOKEN_TYPE_REDIR_APPEND);
		if (!token->next_cmd)
			return (printf("no out file to append"), 1);
		token_type(token->next_cmd, TOKEN_TYPE_OUT_FILE);
	}
	return (0);
}

int	check_pipes(t_cmd *token)
{
	token_type(token, TOKEN_TYPE_PIPE);
	if (!token->prev_token)	
		return (printf("Missing program before the pipe\n"), 1);
//	if (token->prev_token->type != TOKEN_TYPE_UNKNOWN && token->prev_token->type != TOKEN_TYPE_COMMAND)
//	{
//		if (token->prev_token->type != TOKEN_TYPE_DOUBLE_QUOTE && token->prev_token->type != TOKEN_TYPE_SINGLE_QUOTE)
//			return (printf("The previous is not an executable: %s\n", token->prev_token->text));
//	}
	if (!token->next_cmd)
		return (printf("Missing program after the pipe\n"), 1);
	if (token->next_cmd->type != TOKEN_TYPE_UNKNOWN)
		return (printf("The next is not an executable"), 1);
	// printf("++++++++\nPreview token: %s\nCurrent Token: %s\nNext token: %s\n=======\n", token->prev_token->text, token->text, token->next_cmd->text);
	token_type(token->prev_token, TOKEN_TYPE_COMMAND);
	token_type(token->next_cmd, TOKEN_TYPE_COMMAND);
	return (0);
}

int	build_metachars(t_input *input)
{
	int err;
//
	err = 0;
	input->token = input->head;
	while (input->token->next_cmd && !err)
	{
		if	(input->token && !ft_strncmp(input->token->text, "<", 1))
			err = in_redirections(input->token);
		else if	(input->token && !ft_strncmp(input->token->text, ">", 1))
			err = out_redirections(input->token);
		else if	(input->token && !ft_strncmp(input->token->text, "|", 1))
			err = check_pipes(input->token);

		input->token = input->token->next_cmd;
	}
	return (err);
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
	free(cmd_list);
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
//		if (input[cursor] == '|' && ft_strchr("|<>", input[next]))
//			return (printf("Error: | followed by %c\n", input[next]), 1);
	}
	return (0);
}

t_input   *lexer(const char *input)
{
	t_input *cmd_list;
	int     cursor;
	int		err;

	printf("input: %s\n\n", input);
	if (input_sanitize(input))
		return (printf("non-valid input\n"), NULL);
	printf("input sanitized\n");
	cmd_list = init_input();
	if (!cmd_list)
		return (NULL);
	input = ft_strtrim(input, " \t\n\v\f\r");
	cursor = 0;
	while (input[cursor])
		cursor += input_split(input + cursor, cmd_list, cursor);
	err = build_sentence(cmd_list);
	if (err)
		return (printf("string error\n"), cleanup_cmd_list(cmd_list), NULL);
	if (build_metachars(cmd_list))
		return (printf("metachars error\n"), cleanup_cmd_list(cmd_list), NULL);
	test_lexer(cmd_list);
	return (cmd_list);
}

