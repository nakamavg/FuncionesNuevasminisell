/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/08 00:55:19 by dgomez-m         ###   ########.fr       */
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
		//printf("\n");
		rl_on_new_line();
		rl_replace_line("\n", 0);//cosas de duvan magia a mi no me iba kekw
		rl_redisplay();
        }
    	else if (sig == SIGQUIT)
			printf("exit 3 \n");
    
    return ;
}
void init_signals(void)
{
    struct sigaction mshell;
    mshell.sa_handler = handler_int;
    sigaction(SIGINT, &mshell, NULL);
    sigaction(SIGQUIT, &mshell, NULL);
	sigaction(SIGSTOP, &mshell, NULL);

}
void shell_loop(t_shell *shell)
{

	while(1)
    {
        shell->input= readline(shell->prompt);
        
        if (shell->input && *shell->input) 
		{
            add_history(shell->input);
			//check_input(shell);
			command_handler(shell);
        }
		else if (shell->input == NULL)
		{
			ft_putstr_fd("exit \n", STDOUT_FILENO);
			exit(0);
		}
		if(strcmp(shell->input, "exit") == 0)
		{
			free(shell->input);
			exit(0);
		}
        
        printf("\n");
        free(shell->input); 
    }
}

int main(int argc, char **argv, char **duvan)
{
    (void)argc;
    (void)argv;
    t_shell shell;
	ft_getenv(&shell, duvan);
    init_signals();
	get_things(&shell);
	printf("\033[34mMartes locos presentan: \n\033[0m");
	
    shell_loop(&shell);
    return (0);
}
