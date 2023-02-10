/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/10 16:59:48 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pip {
	int		fd_in;
	int		fd_out;
    int		fd_pipe[2];
	char	*cmd1;
	char	*cmd2;
	char	**envp;
}				t_pip;

// utils
void	pip_error_exit(char *msg);
void	pip_error_exit_if(char *msg, int condition);

// input
void	pip_get_input(t_pip *pip, int argc, char **argv, char **envp);

#endif
