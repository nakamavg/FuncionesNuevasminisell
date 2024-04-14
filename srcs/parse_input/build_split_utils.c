/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:25:06 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/14 18:32:25 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void advance_quotes(const char *s, ssize_t *idx)
{
	int quote;

	quote = s[*idx];
	(*idx)++;
	while (s[*idx] && s[*idx] != quote)
		(*idx)++;
}

static void advance_redirects(const char *s, ssize_t *idx)
{
	while (ft_isspace(s[*idx + 1]))
		(*idx)++;
}

ssize_t break_content(const char *s, char c, char **out)
{
	ssize_t idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == '\'' || s[idx] == '\"')
			advance_quotes(s, &idx);
		else if (s[idx] == '<' || s[idx] == '>')
			advance_redirects(s, &idx);
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

size_t	count_words(char const *s, char c)
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

void	free_output(char **output, size_t counter)
{
	while (counter > 0)
		free(output[--counter]);
	free(output);
}
