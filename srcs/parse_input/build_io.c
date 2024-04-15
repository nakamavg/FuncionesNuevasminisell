/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:44:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/15 19:36:23 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_Token_Type	ft_infile_mode(const char *input)
{
	t_Token_Type	mode;

	mode = TOKEN_TYPE_UNKNOWN;
	while (*input)
	{
		if (*input == '<')
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			if (*input && *input == '<')
				mode = TOKEN_TYPE_REDIR_HEREDOC;
			else
				mode = TOKEN_TYPE_REDIR_IN;
		}
		input++;
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

char	*get_redirection(const char *input, char *last_redirection, bool is_heredoc)
{
	size_t	len;

	while (*input && ft_isspace(*input))
		input++;
	if (!*input)
		return (NULL);
	len = 0;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	if (last_redirection != NULL)
	{
		if (access(last_redirection, F_OK) != 0 && !is_heredoc)
			return (last_redirection);
		free(last_redirection);
	}
	return (ft_substr(input, 0, len));
}

char	*ft_infile_content(const char *input)
{
	int		s_quote;
	int		d_quote;
	char	*last_redirection;
	bool	is_heredoc;

	last_redirection = NULL;
	s_quote = 0;
	d_quote = 0;
	is_heredoc = false;
	while (*input)
	{
		set_quote(&s_quote, &d_quote, *input);
		if (*input++ == '<' && s_quote == 0 && d_quote == 0)
		{
			if (*input == '<')
			{
				is_heredoc = true;
				input++;
			}
			last_redirection = get_redirection(input, last_redirection, is_heredoc);
			if (last_redirection == NULL)
				return (NULL);
		}
	}
	return (last_redirection);
}

char	*ft_outfile_content(const char *input)
{
	int		s_quote;
	int		d_quote;
	char	*last_redirection;

	last_redirection = NULL;
	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		set_quote(&s_quote, &d_quote, *input);
		if (*input++ == '>' && s_quote == 0 && d_quote == 0)
		{
			if (*input == '>')
				input++;
			last_redirection = get_redirection(input, last_redirection, true);
			if (last_redirection != NULL)
				out_file_create(last_redirection);
		}
	}
	return (last_redirection);
}
