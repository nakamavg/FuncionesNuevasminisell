/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:44:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/16 20:10:06 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_Token_Type	ft_infile_mode(const char *input, char *last_redir)
{
	t_Token_Type	mode;
	t_Token_Type	redir_type;

	mode = TOKEN_TYPE_UNKNOWN;
	while (*input)
	{
		if (*input++ != '<')
			continue ;
		redir_type = TOKEN_TYPE_REDIR_IN;
		if (*input && *input == '<')
		{
			redir_type = TOKEN_TYPE_REDIR_HEREDOC;
			input++;
		}
		while (*input && ft_isspace(*input))
			input++;
		if (!ft_strncmp(last_redir, input, ft_strlen(last_redir)))
			mode = redir_type;
	}
	return (mode);
}

t_Token_Type	ft_outfile_mode(const char *input)
{
	t_Token_Type	mode;

	mode = TOKEN_TYPE_UNKNOWN;
	while (*input)
	{
		if (*input == '>')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input && *input == '>')
				mode = TOKEN_TYPE_REDIR_APPEND;
			else
				mode = TOKEN_TYPE_REDIR_OUT;
		}
		input++;
	}
	return (mode);
}

char	*get_redirection(const char *input, char *last_redir, bool is_heredoc, bool *save_more)
{
	size_t	len;
	char    *tmp;

	while (*input && ft_isspace(*input))
		input++;
	if (!*input)
		return (NULL);
	len = 0;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	tmp = ft_substr(input, 0, len);
	if (access(tmp, F_OK) != 0 && !is_heredoc)
	{
		*save_more = false;
		if (last_redir)
		free(last_redir);
		return (tmp);
	}
	if (last_redir)
		free(last_redir);
	return (tmp);
}

char	*ft_infile_content(const char *input)
{
	int		s_quote;
	int		d_quote;
	char	*last_redir;
	bool	is_heredoc;
	bool    save_more;

	last_redir = NULL;
	s_quote = 0;
	d_quote = 0;
	save_more = true;
	while (*input)
	{
		is_heredoc = false;
		set_quote(&s_quote, &d_quote, *input);
		if (*input++ == '<' && s_quote == 0 && d_quote == 0)
		{
			if (*input == '<')
			{
				is_heredoc = true;
				input++;
			}
			if (save_more)
				last_redir = get_redirection(input, last_redir, is_heredoc, &save_more);
			if (last_redir == NULL)
				return (NULL);
		}
	}
	return (last_redir);
}

char	*ft_outfile_content(const char *input)
{
	int		s_quote;
	int		d_quote;
	char	*last_redir;
	bool    save_more;

	last_redir = NULL;
	s_quote = 0;
	d_quote = 0;
	save_more = true;
	while (*input)
	{
		set_quote(&s_quote, &d_quote, *input);
		if (*input++ == '>' && s_quote == 0 && d_quote == 0)
		{
			if (*input == '>')
				input++;
			last_redir = get_redirection(input, last_redir, true, &save_more);
			if (last_redir != NULL)
				out_file_create(last_redir);
		}
	}
	return (last_redir);
}
