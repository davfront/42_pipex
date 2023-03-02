/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_dup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:43:00 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/02 16:12:29 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pip_dup2(t_pip *pip, int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		pip_error_exit(pip, "dup2 failed");
	close(fd1);
}
