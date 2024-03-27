/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:10:06 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/27 00:00:10 by alberrod         ###   ########.fr       */
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

int	in_file_open(char *file_read)
{
	int	file_in;

	if (!file_read)
		return (STDIN_FILENO);
	if (access(file_read, F_OK) != 0)
		unix_error("file error", file_read);
	if (access(file_read, R_OK) != 0)
		unix_error("read error", file_read);
	file_in = open(file_read, O_RDONLY, 0444);
	if (file_in == -1)
		unix_error("error when reading the file", file_read);
	return (file_in);
}
