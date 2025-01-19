/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:19:08 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/19 11:19:40 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipx	*ft_init_data(int ac, char *av[], char *evp[])
{
	t_pipx	*data;

	data = ft_calloc(sizeof(t_pipx), 1);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1]) + 1) == 0)
		data->is_here_doc = true;
	else
		data->is_here_doc = false;
	data->i = data->is_here_doc * 1 + 1;
	data->pids = ft_calloc(sizeof(int), ac - 2);
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
