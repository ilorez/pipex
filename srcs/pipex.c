/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/14 17:51:17 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipx	*data;

	if (argc < 5)
	{
		ft_printf("Usage: \n\t%s infile cmd1 cmd2 ... cmdn outfile\n", argv[0]);
		return (EXIT_FAILURE);
	}
	data = ft_calloc(sizeof(t_pipx), 1);
	data->paths = ft_get_paths(envp);
	if (!data->paths)
		ft_free_data(data);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]) + 1) == 0)
		data->i = 2;
	else
		data->i = 1;
	data->argc = argc;
	if (!ft_run_commands(data, argv, envp))
	{
		ft_free_data(data);
		return (EXIT_FAILURE);
	}
	ft_free_data(data);
	return (0);
}
