/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_reset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:53:39 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/16 16:06:27 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_reset(t_pip *pip)
{
	int	i;

	if (pip->fd_in != -1)
		close(pip->fd_in);
	if (pip->fd_out != -1)
		close(pip->fd_out);
	ft_free((void **)&pip->cmd);
	if (pip->fd_pipe)
	{
		i = 0;
		while (i < 2 * (pip->cmd_size - 1))
		{
			if (pip->fd_pipe[i] != -1)
				close(pip->fd_pipe[i]);
			i++;
		}
		ft_free((void **)&pip->fd_pipe);
	}
	ft_free((void **)&pip->limiter);
}
