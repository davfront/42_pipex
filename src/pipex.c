/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/10 17:03:33 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_execute(char *cmd, char **envp)
{
	char	**cmd_argv;

	cmd_argv = ft_split(cmd, ' ');
}

void	pip_child_process(t_pip *pip)
{
	dup2(pip->fd_in, STDIN_FILENO);
	dup2(pip->fd_pipe[1], STDOUT_FILENO);
	close(pip->fd_pipe[0]);
	close(pip->fd_in);
	pip_execute(pip->cmd1, pip->envp); // execve cmd1 for each possible path (see below)
	exit(EXIT_FAILURE);
}

void	pip_parent_process(t_pip *pip)
{
	int status;

	waitpid(-1, &status, 0);
	dup2(pip->fd_pipe[0], STDIN_FILENO);
	dup2(pip->fd_out, STDOUT_FILENO);
	close(pip->fd_pipe[1]);
	close(pip->fd_out);
	pip_execute(pip->cmd2, pip->envp); // execve cmd2 for each possible path (see below)
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
    pid_t	cpid;

	pip_get_input(&pip, argc, argv, envp);
    if (pipe(pip.fd_pipe) == -1)
		pip_error_exit("pipe failed");
    cpid = fork();
	pip_error_exit_if("fork failed", cpid == -1);
	if (cpid == 0)
		pip_child_process(&pip);
	else
		pip_parent_process(&pip);
	return (EXIT_SUCCESS);
}
