/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:26 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/13 18:11:34 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPX_H
# define PIPX_H

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
  int argc;
	int		i;
	char	*path;
	char	**cmds;
}			t_pipx;

// functions
void		ft_child(t_pipx *data, int i, int argc, char *envp[]);
t_bool		ft_open_rw_files(t_pipx **data, char *argv[], int argc);
t_bool		ft_run_commands(int argc, char *argv[], char *envp[],
				char *paths[]);
t_bool		ft_change_fd(int fd, int to);
char		**ft_get_paths(char *envp[]);
char		*ft_get_right_path(char *cmd, char **paths);
t_bool		ft_on_error(t_pipx *data, char **cmds, char *path, char *err_msg);

#endif
