/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 05:40:01 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/12 11:34:13 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:54:16 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 17:56:15 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	break_content(char const *s, char c, char **out)
{
	ssize_t	idx;
	int		quote;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == '\'' || s[idx] == '\"')
		{
			quote = s[idx];
			idx++;
			while (s[idx] && s[idx] != quote)
				idx++;
		}
		if (s[idx] != c)
			idx++;
		else
			break ;
	}
	*out = ft_substr(s, 0, idx);
	if (*out == NULL)
	{
		free(*out);
		return (-1);
	}
	return (idx);
}

static size_t	count_words(char const *s, char c)
{
	size_t	counter;
	int		quote;

	counter = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
		}
		if (*s != c)
		{
			counter++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (counter);
}

static void	free_output(char **output, size_t counter)
{
	while (counter > 0)
		free(output[--counter]);
	free(output);
}

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

void process_in(char **cmd_list, char *in, int *idx)
{
	char    *tmp_cmp;

	if (!cmd_list)
			return ;
	while (cmd_list[*idx])
	{
		tmp_cmp = ft_strtrim(cmd_list[*idx], "<");
		if (check_names(tmp_cmp, in))
			break ;
		free(tmp_cmp);
		(*idx)++;
	}
	if (*tmp_cmp)
		free(tmp_cmp);
	(*idx)++;
}

void process_in_out(char **cmd_list, char *in, char *out, int *idx)
{
	char    *tmp_cmp;

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
void free_cmd_list(char **cmd_list, int up_to_idx)
{
	int idx;

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

char	**cmd_split(const char *text, char *in, char *out)
{
	char	**cmd_list;
	char	*tmp;
	int		idx;
	int		j;

	idx = 0;
	j = 0;

	cmd_list = ft_split_cmd(text);
	if (in || out)
		process_in_out(cmd_list, in, out, &idx);
	if (idx == ft_strlen_pp(cmd_list))
		idx = 0;
	else
		free_cmd_list(cmd_list, idx);
	while (cmd_list[idx])
	{
		tmp = ft_strtrim(cmd_list[idx], " \t\n\v\f\r");
		free(cmd_list[idx++]);
		if (tmp[0] == '>')
		{
			free(tmp);
			break ;
		}
		if (ft_strncmp(tmp, out, ft_strlen(tmp)) && *tmp != '<' && *tmp != '>')
		{
			cmd_list[j++] = ft_strdup(tmp);
		}
		free(tmp);
	}
	cmd_list[j] = NULL;
	return (cmd_list);
}
