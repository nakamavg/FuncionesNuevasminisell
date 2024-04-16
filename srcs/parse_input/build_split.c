/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 05:40:01 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/16 16:34:18 by alberrod         ###   ########.fr       */
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

	if (!cmd_list)
		return ;
	while (cmd_list[*idx])
	{
		tmp_cmp = ft_strtrim(cmd_list[*idx], "<>");
		if (in && check_names(tmp_cmp, in))
		{
			free(tmp_cmp);
			break ;
		}
		if (out && check_names(tmp_cmp, out))
		{
			free(tmp_cmp);
			break ;
		}
		free(tmp_cmp);
		(*idx)++;
	}
	if (*idx < ft_strlen_pp(cmd_list))
		(*idx)++;
}

void	free_cmd_list(char **cmd_list, int up_to_idx)
{
	int	idx;

	if (!cmd_list)
		return ;
	idx = 0;
	while (idx < up_to_idx)
	{
		if (cmd_list[idx])
			free(cmd_list[idx]);
		idx++;
	}
}

void	process_cmd_list(char **cmd_list, char *out, int *idx)
{
	char	*tmp;
	int		jdx;

	jdx = 0;
	while (cmd_list[*idx])
	{
		tmp = ft_strtrim(cmd_list[*idx], " \t\n\v\f\r");
		free(cmd_list[*idx]);
		(*idx)++;
		if (tmp[0] == '>')
		{
			free(tmp);
			break ;
		}
		if (ft_strncmp(tmp, out, ft_strlen(tmp)) && *tmp != '<' && *tmp != '>')
			cmd_list[jdx++] = ft_strdup(tmp);
		free(tmp);
	}
	cmd_list[jdx] = NULL;
}

char	**cmd_split(const char *text, char *in, char *out)
{
	char	**cmd_list;
	int		idx;

	idx = 0;
	cmd_list = ft_split_cmd(text);
	if (in || out)
		process_in_out(cmd_list, in, out, &idx);
	if (idx == ft_strlen_pp(cmd_list))
		idx = 0;
	else
		free_cmd_list(cmd_list, idx);
	process_cmd_list(cmd_list, out, &idx);
	return (cmd_list);
}
