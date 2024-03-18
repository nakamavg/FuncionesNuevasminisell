/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:44:02 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/18 22:47:32 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_input	cmd_list;
//	 lexer("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH | /dev/null' | cat -e");
//	lexer("ls -la | echo \"hola mundo\" | wc -c | echo multiple pipes done | cat -e >>outfile");
	cmd_list = lexer("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >>outfile");
	// lexer("< ~/Desktop/in ls -la | ./echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >> outfile");
//	 lexer("/bin/bash/echo \"hola mundo mundial\" > in3 | <in2 cat");
//	 lexer("'hola ke ase ninio \"|'");
	cleanup_cmd_list(&cmd_list);
    return (0);
}
