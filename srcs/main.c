/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:44:02 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 18:23:10 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_input	cmd_list;
//	 parse_input("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH | /dev/null' | cat -e");
	// parse_input("ls -la | echo \"hola mundo\" | wc -c | echo multiple pipes done | cat -e >>outfile");
	cmd_list = parse_input("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH and this is additional text\" | cat -e >>outfile");
	// parse_input("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH and this is additional text\" | cat -e >>outfile");
	// parse_input("< ~/Desktop/in ls -la | ./echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >> outfile");
//	 parse_input("/bin/bash/echo \"hola mundo mundial\" > in3 | <in2 cat");
	//  cmd_list = parse_input("'hola ke ase $NINIO \"|' | echo $PATH | echo \"$ENV\"");
	cleanup_cmd_list(&cmd_list);
    return (0);
}
