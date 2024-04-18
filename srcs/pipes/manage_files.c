/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:10:06 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/18 08:17:31 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	out_file_open(char *file_write, t_Token_Type write_type)
{
	int	file_out;
	int	write_mode;

	if (!file_write)
		return (STDOUT_FILENO);
	if (write_type == TOKEN_TYPE_REDIR_APPEND)
		write_mode = O_APPEND;
	else
		write_mode = O_TRUNC;
	file_out = open(file_write, O_WRONLY | write_mode, 0644);
	if (file_out == -1)
		unix_error("write error", file_write);
	return (file_out);
}

void	out_file_create(char *file_write)
{
	int	file_out;

	if (!file_write)
		return ;
	if (access(file_write, F_OK) != 0)
	{
		file_out = open(file_write, O_CREAT, 0644);
		close (file_out);
	}
}

static void	parse_here_doc(char *eof)
{
	int		in_file;
	char	*line;

	in_file = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	write(OUT, "> ", ft_strlen("> "));
	line = get_next_line(IN);
	if (!line)
	{
		close(in_file);
		return ;
	}
	while (ft_strncmp(line, eof, ft_strlen(line) - 1))
	{
		write(in_file, line, ft_strlen(line));
		free(line);
		write(OUT, "> ", ft_strlen("> "));
		line = get_next_line(IN);
		if (!line)
			break ;
	}
	free(line);
	close(in_file);
}

int	in_file_open(char *file_read, t_Token_Type infile_mode)
{
	int	file_in;

	if (!file_read)
		return (STDIN_FILENO);
	(void)infile_mode;
	if (infile_mode == TOKEN_TYPE_REDIR_HEREDOC)
	{
		parse_here_doc(file_read);
		file_in = open("/tmp/here_doc", O_RDONLY, 0444);
	}
	else
	{
		if (access(file_read, F_OK) != 0)
			return (unix_error("file error", file_read), -1);
		if (access(file_read, R_OK) != 0)
			return (unix_error("read error", file_read), -1);
		file_in = open(file_read, O_RDONLY, 0444);
	}
	if (file_in == -1)
		return (unix_error("error when reading the file", file_read), -1);
	return (file_in);
}
