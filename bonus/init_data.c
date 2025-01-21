/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:19:08 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 17:54:54 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*ft_init_data(int ac, char *av[], char *evp[])
{
	t_pipex	*data;

	data = ft_calloc(sizeof(t_pipex), 1);
  if (!data)
    return (NULL);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1]) + 1) == 0)
		data->is_here_doc = true;
	else
		data->is_here_doc = false;
	data->i = data->is_here_doc * 1 + 1;
	data->ac = ac;
  data->av = av;
  data->evp = evp;
	data->j = 0;
	data->status = 0;
  data->fd[0] = -1;
  data->fd[1] = -1;
  data->in = -1;
  data->out = -1;
	data->pids = ft_calloc(sizeof(int), ac - 3);
	data->paths = ft_get_paths(evp);
  data->tmpfile = NULL;
  if (!data->paths || !data->pids)
		ft_handle_exit(data, 1);
	return (data);
}
