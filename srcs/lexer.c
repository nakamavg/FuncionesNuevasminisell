/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:18:17 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/06 23:44:28 by alberrod         ###   ########.fr       */
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

void	tokenize_sentence(t_token *token)
{
	if (!ft_strncmp(token->text, "\"", 1))
		token->type = TOKEN_TYPE_DOUBLE_QUOTE;
	else if (!ft_strncmp(token->text, "`", 1))
		token->type = TOKEN_TYPE_BACKTICK;
	else if (!ft_strncmp(token->text, "$", 1))
		token->type = TOKEN_TYPE_EXPAND;
	else
	{
		if (token->prev_token->type == TOKEN_TYPE_BACKTICK)
			token->type = TOKEN_TYPE_VAR;
		else
			token->type = TOKEN_TYPE_STRING;
	}
	printf("token in sentence: %s\n\ttype: %u\n", token->text, token->type);
}

void	build_sentence(t_input *input)
{
	int	closed_sentence;
	// t_token *tmp;

	closed_sentence = 0;
	while (input->token)
	{
		if (!ft_strncmp(input->token->text, "\"", 1))
		{
			input->token = input->token->next_token;
			// printf("token next is: %s\n", input->token->next_token->text);
			while (input->token && ft_strncmp(input->token->text, "\"", 1))
			{
				tokenize_sentence(input->token);
				input->token = input->token->next_token;
			}
			if (input->token)
				closed_sentence = 1;
			if (closed_sentence) 
				closed_sentence = 0;
			else 
			{
				// printf("here it should be a dquote\n");
				// TODO: Exit the program clean when there's an error
				printf("Error: Not closed string used as input\n");
				break ;
			}
				// printf("input format: pending to deal with it\n");
		}


		input->token = input->token->next_token;
	}
}


void   lexer(const char *input)
{
	t_input *input_struct;
	int     cursor;
	int     input_length;

	printf("input: %s\n\n", input);
	input_struct = init_input();
	if (!input_struct)
		return ;
	input_length = ft_strlen(input);
	input = ft_strtrim(input, " \t\n\v\f\r");
	cursor = 0;
	while (input[cursor])
	{
		// printf("\nCursor: %d\nPending str: %s\n\n", cursor, input + cursor);
		cursor += input_split(input + cursor, input_struct, cursor);
	}
	build_sentence(input_struct);
	// input_struct->token = input_struct->head;
	// while (input_struct->token)
	// {
	// 	printf("Token: %s\n\ttext_len: %lu\n\ttype: %u\n", input_struct->token->text, input_struct->token->text_length, input_struct->token->type);
	// 	input_struct->token = input_struct->token->next_token;
	// }
	// printf("Head: %s\n", input_struct->head->text);
}

