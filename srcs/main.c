/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/07 08:07:05 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	lexer("   <\"       'hola $USER son las `datetime`\" 2>> (somewhere) << eof '$PATH /dev/null' | cat -e");
    return (0);
}
