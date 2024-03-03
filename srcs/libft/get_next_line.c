/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 14:02:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/09 17:18:55 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*append_line(char *line, char *next_line)
{
	char	*new_line;
	size_t	len_line;
	size_t	len_next_line;

	len_line = 0;
	len_next_line = 0;
	if (line)
		len_line = ft_strlen(line);
	if (next_line)
		len_next_line = ft_strlen(next_line);
	new_line = ft_calloc((len_line + len_next_line + 1), sizeof(char));
	if (!new_line)
		return (NULL);
	if (line)
		ft_memcpy(new_line, line, len_line);
	if (next_line)
		ft_memcpy(new_line + len_line, next_line, len_next_line);
	new_line[len_line + len_next_line] = '\0';
	return (new_line);
}

static char	*read_file(int fd)
{
	static int	start = 0;
	static int	end = 0;
	char		*line;
	int			idx;
	static char	buffer[BUFFER_SIZE + 1];

	if (start >= end)
	{
		end = read(fd, buffer, BUFFER_SIZE);
		if (end == 0)
			return (NULL);
		if (end == -1)
			return ("ERROR");
		start = 0;
	}
	idx = start;
	while (idx < end)
		if (buffer[idx++] == '\n')
			break ;
	line = ft_calloc(idx - start + 1, sizeof(char));
	if (!line)
		return ("ERROR");
	ft_memcpy(line, buffer + start, idx - start);
	start = idx;
	return (line);
}

char	*get_next_line(int fd)
{
	char	*next_line;
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		next_line = read_file(fd);
		if (next_line == NULL)
			break ;
		if (ft_strncmp(next_line, "ERROR", ft_strlen("ERROR")) == 0)
		{
			free(line);
			return (NULL);
		}
		tmp = append_line(line, next_line);
		free(line);
		free(next_line);
		if (!tmp)
			return (NULL);
		line = tmp;
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}
