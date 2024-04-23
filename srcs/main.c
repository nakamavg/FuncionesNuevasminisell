/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:44:02 by alberrod          #+#    #+#             */
/*   Updated: 2024/04/23 19:39:26 by alberrod         ###   ########.fr       */
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

void	handle_input(t_shell *shell, bool *s_flag)
{
	add_history(shell->input);
	if (parse_input(shell))
		return ;
	*(s_flag) = true;
	init_signals(s_flag);
	command_handler(shell);
	cleanup_cmd_list(&shell->parsed_input);
}

void	shell_loop(t_shell *shell, bool *s_flag)
{
	char	*tmp;

	while (42)
	{
		*(s_flag) = false;
		init_signals(s_flag);
		tmp = readline(shell->prompt);
		shell->input = ft_strtrim(tmp, " \t\n\v\f\r");
		free(tmp);
		if (shell->input && *shell->input)
			handle_input(shell, s_flag);
		else if (shell->input == NULL)
		{
			ft_putstr_fd("exit \n", STDOUT_FILENO);
			free_shell(shell);
			break ;
		}
		if (shell->input)
			free(shell->input);
	}
	if (shell->input)
		free(shell->input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	bool	signal_cmd;

	g_status = 0;
	signal_cmd = false;
	if (argc != 1)
		return (printf("Only call the minishell %sboss\n", PURPLE), 1);
	(void)argv;
	ft_memset(&shell, 0, sizeof(shell));
	ft_getenv(&shell, envp);
	ft_env_split(&shell);
	get_things(&shell, false);
	printf("\033[34mCrazy Tuesdays (reborn) present: \n\033[0m");
	disable_echo_ctrl_c();
	shell_loop(&shell, &signal_cmd);
	return (0);
}
