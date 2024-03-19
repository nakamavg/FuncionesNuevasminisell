/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 21:54:16 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/19 06:14:58 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static ssize_t	break_content(char const *s, char c, char **out)
{
	ssize_t	idx;
	int 	quote;

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
	int 	quote;

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

// count = number of subarrays in out
// Default fail return: -1
char	**ft_split_cmd(char const *s)
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
