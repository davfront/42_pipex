/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/23 21:58:19 by dapereir         ###   ########.fr       */
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
}

static void	pip_create_heredoc_file(t_pip *pip)
{
	int		fd_in;
	int		fd_out;
	char	*line;

	fd_in = dup(STDIN_FILENO);
	fd_out = open(HEREDOC_FILE, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out == -1)
		pip_perror_exit(pip, HEREDOC_FILE);
	ft_putstr_fd(HEREDOC_HEAD, fd_in);
	line = ft_gnl(fd_in);
	while (line && ft_strncmp(line, pip->limiter, ft_strlen(line) - 1) != 0)
	{
		ft_putstr_fd(line, fd_out);
		ft_free((void **)&line);
		ft_putstr_fd(HEREDOC_HEAD, fd_in);
		line = ft_gnl(fd_in);
	}
	ft_free((void **)&line);
	if (close(fd_in) == -1)
		pip_perror_exit(pip, HEREDOC_FILE);
}

static void	pip_get_input_data(t_pip *pip, char **argv)
{
	if (pip->here_doc)
	{
		pip->limiter = argv[2];
		pip_create_heredoc_file(pip);
		pip->fd_in = open(HEREDOC_FILE, O_RDONLY);
		if (pip->fd_in == -1)
		{
			unlink(HEREDOC_FILE);
			pip_perror_exit(pip, HEREDOC_FILE);
		}
	}
	else
	{
		pip->fd_in = open(argv[1], O_RDONLY);
		if (pip->fd_in == -1)
			perror(argv[1]);
	}
}

static void	pip_get_input(t_pip *pip, int argc, char **argv, char **envp)
{
	int	i;

	pip->here_doc = ft_streq(argv[1], "here_doc");
	pip_get_input_data(pip, argv);
	pip->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pip->fd_out == -1)
		perror(argv[argc - 1]);
	pip->cmd_size = argc - 3 - pip->here_doc;
	pip->cmd = ft_calloc(pip->cmd_size, sizeof(char *));
	i = 0;
	while (i < pip->cmd_size)
	{
		pip->cmd[i] = argv[i + 2 + pip->here_doc];
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
