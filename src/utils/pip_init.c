/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:57:31 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/28 17:14:21 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_init(t_pip *pip)
{
	pip->here_doc = 0;
	pip->limiter = NULL;
	pip->fd_in = -1;
	pip->fd_out = -1;
	pip->cmd_size = 0;
	pip->cmd = NULL;
	pip->fd_pipe = NULL;
	pip->envp = NULL;
}
