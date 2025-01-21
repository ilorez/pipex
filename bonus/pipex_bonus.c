/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 17:41:55 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *evp[])
{
	t_pipex	*data;
	int		status;

	if (ac < 5)
	{
		ft_printf("Usage: \n\t%s infile cmd1 cmd2 ... cmdn outfile\n", av[0]);
		ft_printf("\n\t%s here_doc LIMITER cmd1 cmd2 ... cmdn outfile\n",
			av[0]);
		return (EXIT_FAILURE);
	}
	data = ft_init_data(ac, av, evp);
	if (!data)
		return (EXIT_FAILURE);
	status = ft_run_commands(data);
	ft_handle_exit(data, status);
}
