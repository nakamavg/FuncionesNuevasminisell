/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:17:37 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/10 19:30:22 by dgomez-m         ###   ########.fr       */
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
			return (printf("return here doc\n"), TOKEN_TYPE_REDIR_HEREDOC);
		return (TOKEN_TYPE_REDIR_IN);
	}
	return (TOKEN_TYPE_UNKNOWN);
}

char	*ft_infile_content(const char *input)
{
	size_t	len;

	while (*input && ft_isspace(*input))
		input++;
	if (!input)
		return (NULL);
	if (*input == '<')
	{
		input++;
		if (*input == '<')
			input++;
	}
	else
		return (NULL);
	while (*input && ft_isspace(*input))
		input++;
	len = 0;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	return (ft_substr(input, 0, len));
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

	while (*input && *input != '>')
		input++;
	if (!input)
		return (NULL);
	if (*input == '>')
	{
		input++;
		if (*input == '>')
			input++;
	}
	else
		return (NULL);
	while (*input && ft_isspace(*input))
		input++;
	len = 0;
	while (input[len] && !ft_isspace(input[len]))
		len++;
	return (ft_substr(input, 0, len));
}
