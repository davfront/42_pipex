/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_get_input_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/02 17:52:38 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pip_check_input(t_pip *pip, int argc, char **argv)
{
	if (argc == 1 || (argc == 2 && (ft_streq(argv[1], "-h") || \
		ft_streq(argv[1], "--help"))))
	{
		ft_printf(\
"USAGE 1: \
%s [input_file] [command_1] ... [command_n] [output_file]\n", argv[0]);
		ft_printf(\
"USAGE 2: \
%s here_doc [limiter] [command_1] ... [command_n] [output_file]\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	if (argc < 5 + ft_streq(argv[1], "here_doc"))
		pip_error_exit(pip, "Too few arguments");
	if (argc > 3 + CMD_MAX + ft_streq(argv[1], "here_doc"))
	{
		ft_putstr_fd("Too many commands (maximum allowed: ", STDERR_FILENO);
		ft_putnbr_fd(CMD_MAX, STDERR_FILENO);
		ft_putstr_fd(")\n", STDERR_FILENO);
		pip_error_exit(pip, NULL);
	}
}

static void	pip_create_heredoc_file(t_pip *pip)
{
	int		fd_out;
	char	*line;

	fd_out = open(HEREDOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out == -1)
		pip_perror_exit(pip, HEREDOC_FILE);
	ft_putstr_fd(HEREDOC_HEAD, STDIN_FILENO);
	line = ft_gnl(STDIN_FILENO, 0);
	while (line && !ft_streq(line, pip->limiter))
	{
		ft_putstr_fd(line, fd_out);
		ft_free((void **)&line);
		ft_putstr_fd(HEREDOC_HEAD, STDIN_FILENO);
		line = ft_gnl(STDIN_FILENO, 0);
	}
	ft_free((void **)&line);
	ft_gnl(STDIN_FILENO, 1);
	close(fd_out);
}

static void	pip_open_input_output(t_pip *pip, int argc, char **argv)
{
	if (pip->here_doc)
	{
		pip->limiter = ft_strjoin(argv[2], "\n");
		if (!pip->limiter)
			pip_error_exit(pip, "ft_strjoin failed");
		pip_create_heredoc_file(pip);
		pip->fd_in = open(HEREDOC_FILE, O_RDONLY);
		if (pip->fd_in == -1)
			perror(HEREDOC_FILE);
		pip->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
	{
		pip->fd_in = open(argv[1], O_RDONLY);
		if (pip->fd_in == -1)
			perror(argv[1]);
		pip->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (pip->fd_out == -1)
		perror(argv[argc - 1]);
}

void	pip_get_input(t_pip *pip, int argc, char **argv, char **envp)
{
	int	i;

	pip_check_input(pip, argc, argv);
	pip->here_doc = ft_streq(argv[1], "here_doc");
	pip_open_input_output(pip, argc, argv);
	pip->cmd_size = argc - 3 - pip->here_doc;
	pip->cmd = ft_calloc(pip->cmd_size, sizeof(char *));
	pip_error_exit_if(pip, "ft_calloc failed", !pip->cmd);
	i = 0;
	while (i < pip->cmd_size)
	{
		pip->cmd[i] = argv[i + 2 + pip->here_doc];
		i++;
	}
	pip->fd_pipe = ft_calloc(2 * (pip->cmd_size - 1), sizeof(int));
	pip_error_exit_if(pip, "ft_calloc failed", !pip->fd_pipe);
	i = 0;
	while (i < 2 * (pip->cmd_size - 1))
	{
		pip->fd_pipe[i] = -1;
		i++;
	}
	pip->envp = envp;
}
