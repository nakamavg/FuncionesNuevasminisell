/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:44:02 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/10 21:38:56 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status;

void	disable_echo_ctrl_c(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

void	handler_int(int sig)
{
	if (sig == SIGINT)
	{
		disable_echo_ctrl_c();
		rl_on_new_line();
		rl_replace_line("\n", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		printf("exit 3 \n");
	return ;
}

void	init_signals(void)
{
	struct sigaction	mshell;

	ft_memset(&mshell, 0, sizeof(mshell));
	mshell.sa_handler = handler_int;
	sigaction(SIGINT, &mshell, NULL);
	sigaction(SIGQUIT, &mshell, NULL);
}

void	shell_loop(t_shell *shell)
{
	while (1)
	{
		shell->input = readline(shell->prompt);
		if (shell->input && *shell->input)
		{
			add_history(shell->input);
			if (parse_input(shell))
				continue ;
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
	cleanup_cmd_list(&shell->parsed_input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	g_status = 0;
	ft_getenv(&shell, envp);
	ft_env_split(&shell);
	init_signals();
	get_things(&shell);
	printf("\033[34mMartes locos presentan: \n\033[0m");
	shell_loop(&shell);
	return (0);
}
