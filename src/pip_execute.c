/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/02 16:43:04 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**pip_append_backslash_to_pathes(char **pathes)
{
	int		i;
	char	*new_path;

	if (!pathes)
		return (NULL);
	i = 0;
	while (pathes[i])
	{
		new_path = ft_strjoin(pathes[i], "/");
		if (!new_path)
		{
			ft_free_split(pathes);
			return (NULL);
		}
		ft_free((void **)(pathes + i));
		pathes[i] = new_path;
		i++;
	}
	return (pathes);
}

static char	**pip_get_env_pathes(char **envp)
{
	char	**pathes;

	while (envp && *envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5) == *envp)
		{
			pathes = ft_split(*envp + 5, ':');
			if (!pathes)
				ft_putendl_fd("ft_split failed", STDERR_FILENO);
			pathes = pip_append_backslash_to_pathes(pathes);
			return (pathes);
		}
		envp++;
	}
	pathes = ft_split("/usr/local/bin:/usr/bin:/bin", ':');
	if (!pathes)
		ft_putendl_fd("ft_split failed", STDERR_FILENO);
	pathes = pip_append_backslash_to_pathes(pathes);
	return (pathes);
}

static char	*pip_get_binary_path(char *cmd, char **envp)
{
	char	**pathes;
	int		i;
	char	*cmd_path;

	if (!envp)
		return (NULL);
	pathes = pip_get_env_pathes(envp);
	if (!pathes)
		return (NULL);
	i = 0;
	while (pathes[i])
	{
		cmd_path = ft_strjoin(pathes[i], cmd);
		if (!cmd_path || !access(cmd_path, F_OK))
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

static void	pip_cmdnotfound_exit(t_pip *pip, char *cmd_path, char **cmd_argv)
{
	ft_putstr_fd(cmd_argv[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	ft_free((void **)&cmd_path);
	ft_free_split(cmd_argv);
	pip_reset(pip);
	exit(EXIT_COMMAND_FAILURE);
}

void	pip_execute(t_pip *pip, char *cmd, char **envp)
{
	char	**cmd_argv;
	char	*cmd_path;

	cmd_argv = pip_parse_cmd_args(cmd);
	cmd_path = cmd_argv[0];
	if (execve(cmd_path, cmd_argv, envp) != -1)
	{
		ft_free_split(cmd_argv);
		return ;
	}
	cmd_path = NULL;
	if (!ft_strchr(cmd_argv[0], '/'))
		cmd_path = pip_get_binary_path(cmd_argv[0], envp);
	if (!cmd_path || execve(cmd_path, cmd_argv, envp) == -1)
		pip_cmdnotfound_exit(pip, cmd_path, cmd_argv);
	ft_free((void **)&cmd_path);
	ft_free_split(cmd_argv);
}
