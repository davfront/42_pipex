/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/23 21:41:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pip_check_input(t_pip *pip, int argc, char **argv)
{
	if (argc == 1 || (argc == 2 && (ft_streq(argv[1], "-h") || \
		ft_streq(argv[1], "--help"))))
	{
		ft_printf(\
"USAGE: %s [input_file] [command_1] [command_2] [output_file]\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	pip_error_exit_if(pip, "Too few arguments", argc < 5);
	pip_error_exit_if(pip, "Too many arguments", argc > 5);
}

static void	pip_get_input(t_pip *pip, int argc, char **argv, char **envp)
{
	int	i;

	pip->fd_in = open(argv[1], O_RDONLY);
	if (pip->fd_in == -1)
		perror(argv[1]);
	pip->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pip->fd_out == -1)
		perror(argv[argc - 1]);
	pip->cmd_size = argc - 3;
	pip->cmd = ft_calloc(pip->cmd_size, sizeof(char *));
	i = 0;
	while (i < pip->cmd_size)
	{
		pip->cmd[i] = argv[i + 2];
		i++;
	}
	pip->fd_pipe = ft_calloc(2 * (pip->cmd_size - 1), sizeof(int));
	i = 0;
	while (i < 2 * (pip->cmd_size - 1))
	{
		pip->fd_pipe[i] = -1;
		i++;
	}
	pip->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
	int		status;

	pip_init(&pip);
	pip_check_input(&pip, argc, argv);
	pip_get_input(&pip, argc, argv, envp);
	status = pip_pipe(&pip, 0);
	pip_reset(&pip);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}
