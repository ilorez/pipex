/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:07 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/17 16:37:32 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_child_exit(t_pipx *data,char *err_msg)
{ 
  ft_on_error(data->cmds, data->path, "execve");
	ft_free_data(data);
	exit(errno);
}

int	ft_on_error(char **cmds, char *path, char *err_msg)
{
	if (cmds)
		ft_free_str_lst(cmds);
	if (path)
		free(path);
	if (err_msg)
	{
		perror(err_msg);
		return (errno);
	}
	return (0);
}


