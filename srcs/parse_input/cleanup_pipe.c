/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:55:29 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/22 20:35:31 by dgomez-m         ###   ########.fr       */
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
