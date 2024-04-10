/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeoreadline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:42:48 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/03 19:49:04 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


int main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		printf("You wrote: %s\n", line);
		strncmp(line, "exit", 4) == 0 ? exit(0) : 0;
		add_history(line);
		free(line);
	}
	return (0);
}