/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/22 12:10:39 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**pip_get_env_pathes(char **envp)
{
	char	**pathes;

	while (envp && *envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5) == *envp)
		{
			pathes = ft_split(*envp + 5, ':');
			return (pathes);
		}
		envp++;
	}
	return (NULL);
}

static char	*pip_get_binary_path(char *cmd, char **envp)
{
	char	**pathes;
	int		i;
	char	*dir_path;
	char	*cmd_path;

	pathes = pip_get_env_pathes(envp);
	if (!pathes)
		return (NULL);
	i = 0;
	while (pathes[i])
	{
		dir_path = ft_strjoin(pathes[i], "/");
		cmd_path = ft_strjoin(dir_path, cmd);
		ft_free((void **)&dir_path);
		if (!access(cmd_path, F_OK))
		{
			ft_free_split(pathes);
			return (cmd_path);
		}
		ft_free((void **)&cmd_path);
		i++;
	}
	ft_free_split(pathes);
	return (NULL);
}

void	pip_execute(t_pip *pip, char *cmd, char **envp)
{
	char	**cmd_argv;
	char	*cmd_path;

	cmd_argv = pip_parse_cmd_args(cmd);
	cmd_path = cmd_argv[0];
	if (ft_strncmp("./", cmd_argv[0], 2) == 0)
		cmd_path += 2;
	if (execve(cmd_argv[0], cmd_argv, envp) != -1)
	{
		ft_free_split(cmd_argv);
		return ;
	}
	cmd_path = pip_get_binary_path(cmd_argv[0], envp);
	if (!cmd_path || execve(cmd_path, cmd_argv, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_free_split(cmd_argv);
		pip_error_exit(pip, NULL);
	}
	ft_free((void **)&cmd_path);
	ft_free_split(cmd_argv);
}
