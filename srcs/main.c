/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:44:02 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/22 18:42:26y alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_status;

void disable_echo_ctrl_c()
{
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
		rl_replace_line("\n", 0);
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
	// t_input	cmd_list;
	while(1)
    {
        shell->input= readline(shell->prompt);
        if (shell->input && *shell->input) 
		{
			
			// shell->parsed_input = parse_input(shell->input);
			parse_input(shell);
			test_lexer(&shell->parsed_input);
            add_history(shell->input);
			command_handler(shell);
			cleanup_cmd_list(&shell->parsed_input);
        }
		else if (shell->input == NULL)
		{
			ft_putstr_fd("exit \n", STDOUT_FILENO);
			exit(0);
		}

        free(shell->input); 
    }
	
}


int main(int argc, char **argv, char **envp)
{
	// t_input	cmd_list;
	t_shell shell;
	(void)argc;
	(void)argv;
	// cmd_list = parse_input("< in ls -la | echo \"hola mundo\" | ls | echo sup '$USER' | wc -c | echo \"This is the $PATH and this is additional $ENV\" | cat -e >>outfile");
	// cmd_list = parse_input("<in cat -e | cat -e | cat -e >outfile | <in cat -e");
	// cmd_list = parse_input("<in cat -e >outfile");
	// cmd_list = parse_input("ls -la | ls -la");
	// cmd_list = parse_input("ls -l | wc -l");
	// cmd_list = parse_input("<in  cat -e | cat -e >outfile | <in cat -e");
	// cmd_list = parse_input("<in cat -e | cat -e | cat -e  | cat -e");
	ft_getenv(&shell, envp);
	ft_env_split(&shell);
	init_signals();
	get_things(&shell);
	// test_lexer(&cmd_list);
	printf("\033[34mMartes locos presentan: \n\033[0m");
	
    shell_loop(&shell);	
	// int	pid;
	// int	status;

	// pid = fork_process();
	// if (pid == 0)
	// 	run_pipes(cmd_list, envp);
	// waitpid(pid, &status, 0);

	// cleanup_cmd_list(&cmd_list);
    return (0);
}
