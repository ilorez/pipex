/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/14 10:57:53 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**paths;
	t_pipx	*data;

	if (argc < 5)
	{
    ft_printf("Usage: \n\t%s infile cmd1 cmd2 ... cmdn outfile\n", argv[0]);
		return (EXIT_FAILURE);
  }
	paths = ft_get_paths(envp);
  data = ft_calloc(sizeof(t_pipx), 1);
  if (strncmp(argv[1], "heredoc", ft_strlen(argv[1]) + 1) == 0)
	  data->i = 2;
  data->argc = argc;
  //  // get all inputs and put a file discriptior you can use a pip
  //  // after that edit in run commands to accept already open infile
  //  // edit ft_run_commands to open outfile with append flag in case of heredoc
  //  // just done i mean is it like that you should correct some one pipx
	if (!ft_run_commands(data, argv, envp, paths))
		return (free(paths), EXIT_FAILURE);
	free(paths);
	}
	return (0);
}
