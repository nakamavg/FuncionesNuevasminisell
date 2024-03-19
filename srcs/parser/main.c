/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:44:02 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/19 12:44:44 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_input	cmd_list;
//	 lexer("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH | /dev/null' | cat -e");
	// lexer("ls -la | echo \"hola mundo\" | wc -c | echo multiple pipes done | cat -e >>outfile");
	// cmd_list = lexer("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH and this is additional text\" | cat -e >>outfile");
	// lexer("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH and this is additional text\" | cat -e >>outfile");
	// lexer("< ~/Desktop/in ls -la | ./echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >> outfile");
//	 lexer("/bin/bash/echo \"hola mundo mundial\" > in3 | <in2 cat");
	 cmd_list = lexer("'");
	cleanup_cmd_list(&cmd_list);
    return (0);
}
