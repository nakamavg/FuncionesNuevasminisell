/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:31:55 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 02:14:46 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/16 00:41:22 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
//	 lexer("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH | /dev/null' | cat -e");
//	lexer("ls -la | echo \"hola mundo\" | wc -c | echo multiple pipes done | cat -e >>outfile");
//	parser("< in ls -la | echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >>outfile");
	parser("< ~/Desktop/in ls -la | ./echo \"hola mundo\" | wc -c | echo \"This is the $PATH \" | cat -e >> outfile");
	// parser("echo \"hola\" > in3 | <in2 cat");
//	 lexer("'hola ke ase ninio \"|'");
	// lexer("'hola bobo\"|'");
    return (0);
}
