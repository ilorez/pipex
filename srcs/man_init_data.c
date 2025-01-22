/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:19:08 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/22 15:15:13 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "man_pipex.h"

t_pipex	*ft_init_data(int ac, char *av[], char *evp[])
{
	t_pipex	*data;

	data = ft_calloc(sizeof(t_pipex), 1);
	if (!data)
		return (NULL);
	data->i = 1;
	data->ac = ac;
	data->av = av;
	data->evp = evp;
	data->j = 0;
	data->status = 0;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->in = -1;
	data->out = -1;
	data->pids = ft_calloc(sizeof(int), ac - 2);
	data->paths = ft_get_paths(evp);
	if (!data->paths || !data->pids)
		ft_handle_exit(data, 1);
	return (data);
}
