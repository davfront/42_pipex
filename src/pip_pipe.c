/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/23 21:37:52 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pip_child_process_1(t_pip *pip, int level)
{
	int		*fd_pipe;
	int		fd_in;
	int		*fd_pipe_prev;

	fd_pipe = pip->fd_pipe + 2 * level;
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	if (level == 0)
	{
		if (pip->fd_in == -1)
			pip_error_exit(pip, NULL);
		fd_in = pip->fd_in;
	}
	else
	{
		fd_pipe_prev = pip->fd_pipe + 2 * (level - 1);
		fd_in = fd_pipe_prev[0];
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	pip_execute(pip, pip->cmd[level], pip->envp);
	unlink(HEREDOC_FILE);
}

static void	pip_child_process_2(t_pip *pip, int level)
{
	int	*fd_pipe;

	fd_pipe = pip->fd_pipe + 2 * level;
	close(fd_pipe[1]);
	if (pip->cmd_size - level > 2)
		pip_pipe(pip, level + 1);
	else if (pip->cmd_size - level == 2)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[0]);
		if (pip->fd_out == -1)
			pip_error_exit(pip, NULL);
		dup2(pip->fd_out, STDOUT_FILENO);
		close(pip->fd_out);
		pip_execute(pip, pip->cmd[level + 1], pip->envp);
	}
}

int	pip_pipe(t_pip *pip, int level)
{
	pid_t	cpid_1;
	pid_t	cpid_2;
	int		*fd_pipe;
	int		status;

	fd_pipe = pip->fd_pipe + 2 * level;
	if (pipe(fd_pipe) == -1)
		pip_error_exit(pip, "Pipe failed");
	cpid_1 = fork();
	if (cpid_1 == -1)
		pip_error_exit(pip, "Fork failed");
	if (cpid_1 == 0)
		pip_child_process_1(pip, level);
	cpid_2 = fork();
	if (cpid_2 == -1)
		pip_error_exit(pip, "Fork failed");
	if (cpid_2 == 0)
		pip_child_process_2(pip, level);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	status = 0;
	waitpid(cpid_1, &status, 0);
	waitpid(cpid_2, &status, 0);
	return (status);
}
