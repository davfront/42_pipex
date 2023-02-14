/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/14 12:10:03 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*pip_get_binary_path(char *cmd, char **envp);

void	pip_execute(t_pip *pip, char *cmd, char **envp)
{
	char	**cmd_argv;
	char	*cmd_path;

	cmd_argv = ft_split(cmd, ' ');
	cmd_path = pip_get_binary_path(cmd_argv[0], envp);
	if (execve(cmd_path, cmd_argv, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		pip_error_exit(pip, cmd_argv[0]);
	}
	ft_free((void **)&cmd_path);
	ft_free((void **)&cmd_argv);
}

static char	*pip_get_binary_path(char *cmd, char **envp)
{
	char	**pathes;
	char	*dir_path;
	char	*cmd_path;

	while (envp && *envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5) == *envp)
		{
			pathes = ft_split(*envp + 5, ':');
			while (*pathes)
			{
				dir_path = ft_strjoin(*pathes, "/");
				cmd_path = ft_strjoin(dir_path, cmd);
				ft_free((void **)&dir_path);
				if (access(cmd_path, F_OK) == 0)
					return (cmd_path);
				ft_free((void **)&cmd_path);
				pathes++;
			}
			return (*envp);
		}
		envp++;
	}
	return (NULL);
}
