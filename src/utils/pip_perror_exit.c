/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/16 16:09:18 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_perror_exit(t_pip *pip, char *msg)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	if (msg && *msg)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	pip_reset(pip);
	exit(EXIT_FAILURE);
}

void	pip_perror_exit_if(t_pip *pip, char *msg, int condition)
{
	if (condition)
		pip_perror_exit(pip, msg);
}
