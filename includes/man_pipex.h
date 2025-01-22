/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_pipex.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:26 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/22 15:25:11 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAN_PIPEX_H
# define MAN_PIPEX_H

// include
# include "libft.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

// pipex data structure
typedef struct s_pipex
{
	int		fd[2];
	int		*pids;
	int		status;
	int		out;
	int		in;
	int		ac;
	int		j;
	int		i;
	char	**av;
	char	**evp;
	char	*path;
	char	**cmds;
	char	**paths;
}			t_pipex;

// functions

// handle_exit
int			ft_handle_exit(t_pipex *data, int status);

// init data
t_pipex		*ft_init_data(int ac, char *av[], char *evp[]);

// on errors
int			ft_show_error(char *prefix, char *suffix);

// run commands
int			ft_run_commands(t_pipex *data);
int			ft_waitpids(t_pipex *data);
int			ft_get_infile(t_pipex *data);

// child
void		ft_child(t_pipex *data);
void		ft_get_outfile(t_pipex *data);

// utils
t_bool		ft_change_fd(t_pipex *data, int fd, int to);
void		ft_close_pipe(t_pipex *data, t_bool read, t_bool write);
char		**ft_get_paths(char *envp[]);
char		*ft_get_right_path(char *cmd, char **paths);

// wait macros
t_bool		ft_wifexited(int status);
int			ft_wexitstatus(int status);

#endif
