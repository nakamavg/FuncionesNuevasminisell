/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:10:06 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/22 22:31:10 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:32:14 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/20 18:34:33 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:11:38 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/18 01:13:01 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_word_quotes(char *str, int s_quote, int d_quote)
{
	size_t	idx;
	int		jdx;
	char	*out;

	out = ft_calloc(ft_strlen(str) + 1, sizeof(char *));
	idx = 0;
	jdx = 0;
	while (str[idx])
	{
		if (str[idx] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (str[idx] == '\"' && !s_quote)
			d_quote = !d_quote;
		if ((str[idx] != '\'' || d_quote) && (str[idx] != '\"' || s_quote))
			out[jdx++] = str[idx];
		idx++;
	}
	free(str);
	return (out);
}

void	find_special_char(char *cmd, int s_quote, int d_quote, int *cleanup)
{
	int	idx;

	idx = -1;
	while (cmd[++idx])
	{
		set_quote(&s_quote, &d_quote, cmd[idx]);
		if (cmd[idx] == '>' && !d_quote && !s_quote)
		{
			*cleanup = idx;
			return ;
		}
	}
	*cleanup = 0;
}

char	**cleanup_redir_char(char **cmd_list)
{
	int		idx;
	int		cleanup;
	char	**tmp_list;

	if (!cmd_list)
		return (NULL);
	idx = -1;
	tmp_list = ft_calloc(ft_strlen_pp(cmd_list) + 1, sizeof(char *));
	while (cmd_list[++idx])
	{
		find_special_char(cmd_list[idx], 0, 0, &cleanup);
		if (cleanup)
			tmp_list[idx] = ft_substr(cmd_list[idx], 0, cleanup);
		else
			tmp_list[idx] = ft_strdup(cmd_list[idx]);
	}
	free_array_of_strings(cmd_list);
	return (tmp_list);
}

t_cmd	*init_pipe(const char *text, size_t text_length, int initial_idx,
		t_shell *shell)
{
	t_cmd	*token;

	if (ft_strchr(" \t\n\v\f\r", *text) && text_length <= 1)
		return (NULL);
	token = malloc(sizeof(t_cmd));
	if (!token)
		return (NULL);
	token->text = ft_substr(text, initial_idx, text_length);
	token->infile = ft_infile_content(token->text, 0, 0);
	if (token->infile)
		token->infile_mode = ft_infile_mode(token->text, token->infile);
	token->outfile = ft_outfile_content(token->text);
	if (token->outfile)
		token->write_mode = ft_outfile_mode(token->text);
	token->cmd_list = cmd_split(token->text, token->infile, token->outfile);
	token->cmd_list = expand_variable(token->cmd_list, shell, 0, 0);
	token->cmd_list = cleanup_redir_char(token->cmd_list);
	token->cmd_list = trim_quotes(token->cmd_list);
	token->next_cmd = NULL;
	token->prev_token = NULL;
	return (token);
}

void	add_pipe(t_input *cmd_list, t_cmd *new_token)
{
	t_cmd	*tmp;

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
}
