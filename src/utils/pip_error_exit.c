/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_error_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/16 11:53:54 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_error_exit(t_pip *pip, char *msg)
{
	if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	pip_reset(pip);
	exit(EXIT_FAILURE);
}

void	pip_error_exit_if(t_pip *pip, char *msg, int condition)
{
	if (condition)
		pip_error_exit(pip, msg);
}
