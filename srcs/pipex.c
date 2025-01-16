/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/16 13:27:26 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipx	*data;
  int status;

	if (argc < 5)
	{
		ft_printf("Usage: \n\t%s infile cmd1 cmd2 ... cmdn outfile\n", argv[0]);
		return (EXIT_FAILURE);
	}
	data = ft_calloc(sizeof(t_pipx), 1);
	data->paths = ft_get_paths(envp);
	if (!data->paths)
		return (ft_free_data(data), EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) + 1) == 0)
		data->i = 2;
	else
		data->i = 1;
	data->argc = argc;
  data->status = 0;
	status = ft_run_commands(data, argv, envp);
	ft_free_data(data);
	return (status);
}
