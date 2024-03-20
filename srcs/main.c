/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:39:45 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/20 12:17:52 by dgomez-m         ###   ########.fr       */
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

}
void shell_loop(t_shell *shell)
{
	//t_input	cmd_list;
	while(1)
    {
        shell->input= readline(shell->prompt);
		//cmd_list = lexer(shell->input);
        if (shell->input && *shell->input) 
		{
			
            add_history(shell->input);
			//cmd_list = lexer(shell->input);
			command_handler(shell);
	//cleanup_cmd_list(&cmd_list);
        }
		else if (shell->input == NULL)
		{
			ft_putstr_fd("exit \n", STDOUT_FILENO);
			exit(0);
		}
		
        free(shell->input); 
    }
	
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_shell shell;
	ft_getenv(&shell, env);
	ft_env_split(&shell);
    init_signals();
	get_things(&shell);
	printf("\033[34mMartes locos presentan: \n\033[0m");
	
    shell_loop(&shell);
    return (0);
}
