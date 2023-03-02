/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/02 19:16:45 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pip_set_all_fd_pipes(t_pip *pip)
{
	int	i;
	int	*fd_pipe;

	i = 0;
	while (i < pip->cmd_size - 1)
	{
		fd_pipe = pip->fd_pipe + 2 * i;
		if (pipe(fd_pipe) == -1)
			pip_error_exit(pip, "Pipe failed");
		i++;
	}
}

static void	pip_close_all_fd_pipes(t_pip *pip)
{
	int	i;

	i = 0;
	while (i < 2 * (pip->cmd_size - 1))
	{
		close(pip->fd_pipe[i]);
		i++;
	}
}

static void	pip_child_process(t_pip *pip, int cmd_id)
{
	if (cmd_id == 0)
	{
		if (pip->fd_in == -1)
			pip_error_exit(pip, NULL);
		pip_dup2(pip, pip->fd_in, STDIN_FILENO);
	}
	else
		pip_dup2(pip, pip->fd_pipe[2 * (cmd_id - 1)], STDIN_FILENO);
	if (cmd_id == pip->cmd_size - 1)
	{
		if (pip->fd_out == -1)
			pip_error_exit(pip, NULL);
		pip_dup2(pip, pip->fd_out, STDOUT_FILENO);
	}
	else
		pip_dup2(pip, pip->fd_pipe[2 * cmd_id + 1], STDOUT_FILENO);
	pip_close_all_fd_pipes(pip);
	pip_execute(pip, pip->cmd[cmd_id], pip->envp);
}

int	pip_pipe(t_pip *pip)
{
	pid_t	cpid[CMD_MAX];
	int		i;
	int		status;

	pip_set_all_fd_pipes(pip);
	i = 0;
	while (i < pip->cmd_size)
	{
		cpid[i] = fork();
		if (cpid[i] == -1)
			pip_error_exit(pip, "Fork failed");
		if (cpid[i] == 0)
			pip_child_process(pip, i);
		i++;
	}
	pip_close_all_fd_pipes(pip);
	i = 0;
	while (i < pip->cmd_size - 1)
	{
		waitpid(cpid[i], NULL, 0);
		i++;
	}
	waitpid(cpid[pip->cmd_size - 1], &status, 0);
	return (status);
}
