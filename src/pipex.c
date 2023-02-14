/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/14 12:37:41 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pip_child_process(t_pip *pip);
static void	pip_parent_process(t_pip *pip);

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
	pid_t	cpid;

	pip_init(&pip);
	pip_get_input(&pip, argc, argv, envp);
	if (pipe(pip.fd_pipe) == -1)
		pip_error_exit(&pip, "Pipe failed");
	cpid = fork();
	if (cpid == -1)
		pip_error_exit(&pip, "Fork failed");
	if (cpid == 0)
		pip_child_process(&pip);
	else
		pip_parent_process(&pip);
	return (EXIT_SUCCESS);
}

static void	pip_child_process(t_pip *pip)
{
	dup2(pip->fd_in, STDIN_FILENO);
	dup2(pip->fd_pipe[1], STDOUT_FILENO);
	close(pip->fd_pipe[0]);
	close(pip->fd_in);
	pip_execute(pip, pip->cmd1, pip->envp);
	exit(EXIT_FAILURE);
}

static void	pip_parent_process(t_pip *pip)
{
	int	status;

	waitpid(-1, &status, 0);
	dup2(pip->fd_pipe[0], STDIN_FILENO);
	dup2(pip->fd_out, STDOUT_FILENO);
	close(pip->fd_pipe[1]);
	close(pip->fd_out);
	pip_execute(pip, pip->cmd2, pip->envp);
	exit(EXIT_FAILURE);
}
