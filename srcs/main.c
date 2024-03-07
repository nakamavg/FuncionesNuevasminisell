/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/07 12:31:42 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	// lexer("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH | /dev/null' | cat -e");
	lexer("ls -la | echo \"hola mundo\" | wc -c | echo multiple pipes done | <cat -e >>outfile");
    return (0);
}
