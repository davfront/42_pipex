/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:25:40 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/28 17:17:56 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pip	pip;
	int		status;

	pip_init(&pip);
	pip_get_input(&pip, argc, argv, envp);
	status = pip_pipe(&pip, 0);
	pip_reset(&pip);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}
