/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/12 03:19:00 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
//	 lexer("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH | /dev/null' | cat -e");
//	lexer("ls -la | echo \"hola mundo\" | wc -c | echo multiple pipes done | cat -e >>outfile");
//	parser("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >>outfile");
	parser("< in ls -la | ./echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >> outfile");
    return (0);
}
