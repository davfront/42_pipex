/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/02/16 15:06:42 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# define HEREDOC_FILE	".heredoc"
# define HEREDOC_HEAD	"pipe heredoc> "

typedef struct s_pip {
	int		here_doc;
	char	*limiter;
	int		fd_in;
	int		fd_out;
	int		cmd_size;
	char	**cmd;
	int		*fd_pipe;
	char	**envp;
}				t_pip;

void	pip_init(t_pip *pip);
void	pip_reset(t_pip *pip);
void	pip_error_exit(t_pip *pip, char *msg);
void	pip_error_exit_if(t_pip *pip, char *msg, int condition);
void	pip_perror_exit(t_pip *pip, char *msg);
void	pip_perror_exit_if(t_pip *pip, char *msg, int condition);
void	pip_execute(t_pip *pip, char *cmd, char **envp);
void	pip_pipe(t_pip *pip, int level);

#endif
