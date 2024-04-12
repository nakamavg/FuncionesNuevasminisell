/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:44:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/12 14:27:19 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_Token_Type	ft_infile_mode(const char *input)
{
	while (ft_isspace(*input))
		input++;
	if (!input)
		return (TOKEN_TYPE_UNKNOWN);
	if (*input == '<')
	{
		if (*(input + 1) == '<')
			return (printf("return (here doc\n"), TOKEN_TYPE_REDIR_HEREDOC);
		return (TOKEN_TYPE_REDIR_IN);
	}
	return (TOKEN_TYPE_UNKNOWN);
}

char	*ft_infile_content(const char *input)
{
	size_t	len;
	int		s_quote;
	int		d_quote;
	char	*last_redirection;

	last_redirection = NULL;
	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		s_quote = handle_quote(*input, s_quote, &d_quote, '\'');
		d_quote = handle_quote(*input, d_quote, &s_quote, '"');
		if (*input == '<' && s_quote == 0 && d_quote == 0)
		{
			input++;
			if (*input == '<')
				input++;
			while (*input && ft_isspace(*input))
				input++;
			if (!*input)
				break ;
			len = 0;
			while (input[len] && !ft_isspace(input[len]))
				len++;
			if (last_redirection != NULL)
			{
				if (access(last_redirection, F_OK) != 0)
					break ;
				free(last_redirection);
			}
			last_redirection = ft_substr(input, 0, len);
		}
		input++;
	}
	return (last_redirection);
}

t_Token_Type	ft_outfile_mode(const char *input)
{
	while (*input && *input != '>')
		input++;
	if (!input)
		return (TOKEN_TYPE_UNKNOWN);
	if (*input == '>')
	{
		if (*++input == '>')
			return (TOKEN_TYPE_REDIR_APPEND);
		return (TOKEN_TYPE_REDIR_OUT);
	}
	return (TOKEN_TYPE_UNKNOWN);
}

char	*ft_outfile_content(const char *input)
{
	size_t	len;
	int		s_quote;
	int		d_quote;
	char	*last_redirection;

	last_redirection = NULL;
	s_quote = 0;
	d_quote = 0;
	while (*input)
	{
		s_quote = handle_quote(*input, s_quote, &d_quote, '\'');
		d_quote = handle_quote(*input, d_quote, &s_quote, '"');
		if (*input == '>' && s_quote == 0 && d_quote == 0)
		{
			input++;
			if (*input == '>')
				input++;
			while (*input && ft_isspace(*input))
				input++;
			if (!*input)
				break ;
			len = 0;
			while (input[len] && !ft_isspace(input[len]))
				len++;
			if (last_redirection != NULL)
			{
				out_file_create(last_redirection);
				free(last_redirection);
			}
			last_redirection = ft_substr(input, 0, len);
		}
		input++;
	}
	return (last_redirection);
}
