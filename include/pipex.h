/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapereir <dapereir@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:28:19 by dapereir          #+#    #+#             */
/*   Updated: 2023/03/02 17:59:30 by dapereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <libft.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define EXIT_COMMAND_FAILURE	127

# define CMD_MAX	64

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
void	pip_perror(char *msg);
void	pip_perror_exit(t_pip *pip, char *msg);
void	pip_perror_exit_if(t_pip *pip, char *msg, int condition);
void	pip_dup2(t_pip *pip, int fd1, int fd2);
void	pip_update_quote(char *quote, char const *prev, char const *curr);
size_t	pip_count_cmd_args(char const *s);
char	*pip_get_cmd_arg(char const *s);
char	**pip_parse_cmd_args(char const *s);
void	pip_execute(t_pip *pip, char *cmd, char **envp);
int		pip_pipe(t_pip *pip);
void	pip_get_input(t_pip *pip, int argc, char **argv, char **envp);

#endif
