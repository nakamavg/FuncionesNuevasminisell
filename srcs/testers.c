/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:23:51 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/19 08:55:24 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_lexer(t_input *cmd_list)
{
    char **cmd_list_temp;

    cmd_list->token = cmd_list->head;
    while (cmd_list->token) {
        if (cmd_list->token->text)
        printf("\nPIPE_BLOCK: %s\n", cmd_list->token->text);
        printf("\tCMD_LST: ");
        cmd_list_temp = cmd_list->token->cmd_list;
        while (*cmd_list_temp)
        {
            printf("[%s]", *cmd_list_temp);
            cmd_list_temp++;
        }
        printf("\n");
        printf("\tthe infile is: %s\n\tthe oufile is: %s\n", cmd_list->token->infile, cmd_list->token->outfile);
        cmd_list->token = cmd_list->token->next_cmd;
    }
}