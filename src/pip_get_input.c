/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_get_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:17:45 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/14 12:34:26 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_get_input(t_pip *pip, int argc, char **argv, char **envp)
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
	pip->fd_in = open(argv[1], O_RDONLY);
	if (pip->fd_in == -1)
		pip_perror_exit(pip, argv[1]);
	pip->fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pip->fd_out == -1)
		pip_perror_exit(pip, argv[4]);
	pip->cmd1 = argv[2];
	pip->cmd2 = argv[3];
	pip->envp = envp;
}
