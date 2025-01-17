/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/17 16:37:25 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipx *ft_init_data(int ac, char *av[], char *evp[])
{
	t_pipx	*data;

  data = ft_calloc(sizeof(t_pipx), 1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1]) + 1) == 0)
		data->i = 2;
	else
		data->i = 1;
	data->pids = ft_calloc(sizeof(int), ac - data->i - 1);
	data->paths = ft_get_paths(evp);
	if (!data->paths)
  {
		ft_free_data(data);
    return (NULL);
  }
	data->argc = ac;
	data->j = 0;
	data->status = 0;
  return (data);
}

int	main(int ac, char *av[], char *evp[])
{
	t_pipx	*data;
	int		status;

	if (argc < 5)
	{
		ft_printf("Usage: \n\t%s infile cmd1 cmd2 ... cmdn outfile\n", argv[0]);
		return (EXIT_FAILURE);
	}
  data = ft_init_data(ac, av, evp);
  if (!data)
		return (EXIT_FAILURE);
	status = ft_run_commands(data, av, evp);
	ft_free_data(data);
	return (status);
}
