/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:05:20 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/23 15:28:20 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_perror_exit(t_pip *pip, char *msg)
{
	perror(msg);
	pip_reset(pip);
	exit(EXIT_FAILURE);
}

void	pip_perror_exit_if(t_pip *pip, char *msg, int condition)
{
	if (condition)
		pip_perror_exit(pip, msg);
}
