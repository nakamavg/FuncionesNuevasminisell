/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/03 18:36:56 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler_int(int sig)
{
    if (sig == SIGINT)
        {
    printf("handler_int\n");
            ft_printf("\n");
            rl_on_new_line(); //regresa el cursor al inicio de la linea
            rl_replace_line("", 0);//limpia la linea para que no se vea el ^C
            rl_redisplay();//redibuja la linea
        }
    else if (sig == SIGQUIT)
        {
            printf("handler_quit\n");
            ft_putstr_fd("Quit: \n", STDERR_FILENO);
            ft_putnbr_fd(sig, STDERR_FILENO);
            ft_putchar_fd('\n', STDERR_FILENO);
        }
    
    return ;
}
void init_signals(void)
{
    struct sigaction mshell;
    mshell.sa_handler = handler_int;
    sigaction(SIGINT, &mshell, NULL);
    sigaction(SIGQUIT, &mshell, NULL);

}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    init_signals();
    
    
    
    char *rl;
    while(1)
    {
        rl = readline("minishell: ");
        
        if (rl && *rl) {
            add_history(rl);  
        }
        
        printf("\n");
        free(rl); 
    }
    return (0);
}
