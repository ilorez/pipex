/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:26 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/19 16:25:38 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// include
# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>

// pipex data structure
typedef struct s_pipex
{
	int		fd[2];
	int		*pids;
	t_bool	is_here_doc;
	int		status;
	int		out;
	int		in;
	int		ac;
  char **av;
  char **evp;
	int		i;
	int		j;
	char	*path;
	char	**cmds;
	char	**paths;
}			t_pipex;

// functions

// pipex
t_pipex		*ft_init_data(int ac, char *av[], char *evp[]);

#endif
