/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/14 13:51:24 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (ft_strncmp(argv[1], "heredoc", ft_strlen(argv[1]) + 1) == 0)
		data->i = 2;
	else
		data->i = 1;
	data->argc = argc;
	if (!ft_run_commands(data, argv, envp, paths))
  {
    free(data);
    free(paths);
		return (EXIT_FAILURE);
  }
  free(data);
	ft_free_str_lst(paths);
	return (0);
}
