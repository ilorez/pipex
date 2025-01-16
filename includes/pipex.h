/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:26 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/16 12:20:38 by znajdaou         ###   ########.fr       */
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
	int		pid;
	int		outfile;
	int		infile;
	int		argc;
	int		i;
	char	*path;
	char	**cmds;
	char	**paths;
}			t_pipx;

// functions
// run commands
void		ft_child(t_pipx *data, char *envp[], char *argv[]);
int			ft_run_commands(t_pipx *data, char *argv[], char *envp[]);
int			ft_open_rw_files(t_pipx **data, char *argv[]);
void		ft_read_from_input(t_pipx *data, char *av[]);

// utils
t_bool		ft_change_fd(int fd, int to);
char		**ft_get_paths(char *envp[]);
char		*ft_get_right_path(char *cmd, char **paths);
int			ft_on_error(char **cmds, char *path, char *err_msg);
void		ft_free_data(t_pipx *data);

// wait macros
t_bool		wifexited(int status);
int			wexitstatus(int status);

#endif
