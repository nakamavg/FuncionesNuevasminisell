/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_raw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:46:59 by alberrod          #+#    #+#             */
/*   Updated: 2024/03/24 19:47:32 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unix_error(char *mssg, char *str)
{
	if (!str)
		ft_fd_printf(STDERR_FILENO, "%s: %s\n", mssg, strerror(errno));
	else
		ft_fd_printf(STDERR_FILENO, "<%s> %s: %s\n",
			str, mssg, strerror(errno));
	exit (127);
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		unix_error("fork error", NULL);
	return (pid);
}
void	create_pipes(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		unix_error("pipe error", NULL);
}

int	out_file_open(char *file_write, t_Token_Type write_type)
{
	int	file_out;
	int	write_mode;

	if (!file_write)
		return (STDOUT_FILENO);
	if (write_type == TOKEN_TYPE_REDIR_APPEND)	
		write_mode = O_APPEND;
	else
		write_mode = O_TRUNC;
	file_out = open(file_write, O_WRONLY | write_mode, 0644);
	if (file_out == -1)
		unix_error("write error", file_write);
	return (file_out);
}

void	out_file_create(char *file_write)
{
	int	file_out;

	if (!file_write)
		return ;
	if (access(file_write, F_OK) != 0)
	{
		file_out = open(file_write, O_CREAT, 0644);
		close (file_out);
	}
}

int	in_file_open(char *file_read)
{
	int	file_in;

	if (!file_read)
		return (STDIN_FILENO);
	if (access(file_read, F_OK) != 0)
		unix_error("file error", file_read);
	if (access(file_read, R_OK) != 0)
		unix_error("read error", file_read);
	file_in = open(file_read, O_RDONLY, 0444);
	if (file_in == -1)
		unix_error("error when reading the file", file_read);
	return (file_in);
}

static char	**get_path_array(char **envp)
{
	char	**path_env;
	char	**path_array;

	path_array = NULL;
	path_env = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_env = ft_split(*envp, '=');
			path_array = ft_split(path_env[1], ':');
			break ;
		}
		envp++;
	}
	// free_array(path_env);
	return (path_array);
}

char	*extract_path(char **envp, char *cmd)
{
	char	**path_array;
	char	*exec_path;
	int		idx;

	path_array = get_path_array(envp);
	if (!path_array)
		return (NULL);
	idx = 0;
	while (path_array[idx])
	{
		exec_path = ft_sprintf("%s/%s", path_array[idx], cmd);
		if (access(exec_path, X_OK) == 0)
			return (exec_path);
		free(path_array[idx++]);
		free(exec_path);
	}
	free(path_array);
	return (NULL);
}

static void	exec_cmd(char **cmd, char **envp)
{
	char	*path;

	path = extract_path(envp, cmd[0]);
	if (!path)
		unix_error("command error", cmd[0]);
	if (execve(path, cmd, envp) == -1)
	{
		// cleanup(cmd);
		free(path);
		unix_error("execve error", NULL);
	}
}


void	advance_pipe(int prev_pipe[2], int next_pipe[2])
{
	prev_pipe[STDIN_FILENO] = next_pipe[STDIN_FILENO];
	prev_pipe[STDOUT_FILENO] = next_pipe[STDOUT_FILENO];
}


void run_process(char **cmd, char **envp, int pipe_in[2], int pipe_out[2]) {
    int pid;

    pid = fork_process();
    if (pid == 0) {
		printf("\n\tfirst cmd: %s\n\tpipe_fd[in]: %d\n\tpipe_out[out]: %d\n\n", cmd[0], pipe_in[0], pipe_out[1]);
        if (pipe_in[0] != STDIN_FILENO) {
            dup2(pipe_in[0], STDIN_FILENO);
            close(pipe_in[0]);
        }
        if (pipe_out[1] != STDOUT_FILENO) {
            dup2(pipe_out[1], STDOUT_FILENO);
            close(pipe_out[1]);
        }
        exec_cmd(cmd, envp);
    }
    if (pipe_in[0] != STDIN_FILENO) {
        close(pipe_in[0]);
    }
    if (pipe_out[1] != STDOUT_FILENO) {
        close(pipe_out[1]);
    }
}

void run_pipes(t_input cmd_input, char **envp)
{
    t_cmd *pipe;
    int prev_pipe[2] = {-1, -1};
    pipe = cmd_input.head;

    while (pipe)
    {
        int next_pipe[2] = {-1, -1};

        if (pipe->outfile)
            out_file_create(pipe->outfile);

        if (pipe->next_cmd)
            create_pipes(next_pipe);

        if (pipe->outfile)
            next_pipe[STDOUT_FILENO] = out_file_open(pipe->outfile, pipe->write_mode);
        else if (!pipe->next_cmd)
            next_pipe[STDOUT_FILENO] = STDOUT_FILENO;

        if (pipe->infile)
            prev_pipe[STDIN_FILENO] = in_file_open(pipe->infile);
        else if (pipe == cmd_input.head)
            prev_pipe[STDIN_FILENO] = STDIN_FILENO;

        run_process(pipe->cmd_list, envp, prev_pipe, next_pipe);
        advance_pipe(prev_pipe, next_pipe);
        pipe = pipe->next_cmd;
    }
	if (prev_pipe[STDIN_FILENO] != STDIN_FILENO)
		close(prev_pipe[STDIN_FILENO]);
}