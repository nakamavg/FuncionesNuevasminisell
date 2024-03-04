/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/04 04:32:14 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void disable_echo_ctrl_c() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(0, TCSANOW, &term);
}

void handler_int(int sig)
{
    if (sig == SIGINT)
		{
			disable_echo_ctrl_c();
			//nueva linea
			rl_replace_line("", 0);
			rl_on_new_line();
			ft_putstr_fd("\n", STDERR_FILENO);
			ft_putstr_fd("  ", STDIN_FILENO);
			//volver a la ejecucion del programa	
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
