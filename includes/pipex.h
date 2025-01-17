/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:26 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/17 17:29:32 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// include
# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

// pipx data structure
typedef struct s_pipx
{
	int		fd[2];
	int		*pids;
	t_bool	is_here_doc;
	int		status;
	int		outfile;
	int		infile;
	int		argc;
	int		i;
	int		j;
	char	*path;
	char	**cmds;
	char	**paths;
}			t_pipx;

// functions

// pipex
t_pipx		*ft_init_data(int ac, char *av[], char *evp[]);

// here_doc
void		ft_here_doc(int fd, char *eof);

// on_error
void		ft_child_exit(t_pipx *data, char *err_msg);
int			ft_on_error(char **cmds, char *path, char *err_msg);

// run commands
int			ft_run_commands(t_pipx *data, char *argv[], char *envp[]);
int			ft_waitpids(t_pipx *data);
void		ft_child(t_pipx *data, char *envp[], char **argv);
int			ft_get_infile(t_pipx *data, char *argv[]);

// utils
t_bool		ft_change_fd(int fd, int to);
char		**ft_get_paths(char *envp[]);
char		*ft_get_right_path(char *cmd, char **paths);
void		ft_free_data(t_pipx *data);

// wait macros
t_bool		ft_wifexited(int status);
int			ft_wexitstatus(int status);

#endif
