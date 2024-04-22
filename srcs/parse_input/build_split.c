/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 01:32:12 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/22 23:04:00 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 05:40:01 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/20 18:36:13 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_cmd(char const *s)
{
	char	**out;
	ssize_t	idx;
	size_t	count;

	out = ft_calloc(count_words(s, ' ') + 1, sizeof(char *));
	if (out == NULL)
		return (NULL);
	count = -1;
	while (*s)
	{
		if (*s != ' ')
		{
			idx = break_content(s, ' ', &out[++count]);
			if (idx == -1)
			{
				free_output(out, count);
				return (NULL);
			}
			s += idx;
		}
		else
			s++;
	}
	return (out);
}

void	process_in_out(char **cmd_list, char *in, char *out, int *idx)
{
	char	*tmp_cmp;
	int		redir;

	redir = 0;
	if (!cmd_list)
		return ;
	while (cmd_list[*idx])
	{
		if (ft_strchr(cmd_list[*idx], '<'))
			redir = 1;
		if (ft_strchr(cmd_list[*idx], '>'))
			redir = 2;
		tmp_cmp = ft_strtrim(cmd_list[*idx], "<>\"\'");
		if (redir == 1 && in && check_names(tmp_cmp, in))
			break ;
		if (redir == 2 && out && check_names(tmp_cmp, out))
			break ;
		free(tmp_cmp);
		tmp_cmp = NULL;
		(*idx)++;
	}
	if (tmp_cmp != NULL)
		free(tmp_cmp);
	if (*idx < ft_strlen_pp(cmd_list))
		(*idx)++;
}

char	**process_cmd_list(char **cmd_list, int *idx)
{
	char	**new_list;
	char	*tmp;
	int		jdx;
	int		new_list_size;

	new_list_size = ft_strlen_pp(cmd_list);
	new_list = (char **)malloc((new_list_size + 1) * sizeof(char *));
	jdx = 0;
	while (cmd_list[*idx])
	{
		tmp = ft_strtrim(cmd_list[*idx], " \t\n\v\f\r");
		(*idx)++;
		if (tmp[0] == '>')
		{
			free(tmp);
			break ;
		}
		new_list[jdx++] = ft_strdup(tmp);
		free(tmp);
	}
	new_list[jdx] = NULL;
	return (new_list);
}

char	**cmd_split(const char *text, char *in, char *out)
{
	char	**cmd_list;
	char	**new_list;
	int		idx;

	idx = 0;
	cmd_list = ft_split_cmd(text);
	if (in || out)
		process_in_out(cmd_list, in, out, &idx);
	if (idx == ft_strlen_pp(cmd_list))
		idx = 0;
	new_list = process_cmd_list(cmd_list, &idx);
	free_array_of_strings(cmd_list);
	return (new_list);
}

char	**trim_quotes(char **cmd_list)
{
	int		idx;
	char	**tmp_list;

	tmp_list = ft_calloc(ft_strlen_pp(cmd_list) + 1, sizeof(char *));
	idx = -1;
	while (cmd_list[++idx])
		tmp_list[idx] = trim_word_quotes(cmd_list[idx], 0, 0);
	free(cmd_list);
	return (tmp_list);
}
