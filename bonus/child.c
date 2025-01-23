/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:33:06 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/23 11:37:01 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * this function use for child processes
 * */
void	ft_child(t_pipex *data)
{
	close((data->fd)[0]);
	(data->fd)[0] = -1;
	data->cmds = ft_split((data->av)[data->i], ' ');
	data->path = ft_get_right_path(data->cmds[0], data->paths);
	if (data->i < data->ac - 2)
		ft_change_fd(data, (data->fd)[1], STDOUT_FILENO);
	else
		ft_get_outfile(data);
	(data->fd)[1] = -1;
	if (data->in < 0)
		ft_change_fd(data, open("/dev/null", O_RDONLY), STDIN_FILENO);
	else
		ft_change_fd(data, data->in, STDIN_FILENO);
	execve(data->path, data->cmds, data->evp);
	ft_putstr_fd("pipex: ", STDERR_FILENO);
  perror((data->cmds)[0]);
  if (errno == 2)
	  ft_handle_exit(data, 127);
  else if (errno == 13)
	  ft_handle_exit(data, 126);
  else
	  ft_handle_exit(data, errno);
}

void	ft_get_outfile(t_pipex *data)
{
	if (data->is_here_doc)
		data->out = open((data->av)[data->ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		data->out = open((data->av)[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
	if (data->out == -1)
	{
		ft_putstr_fd("pipex: cannot create ", STDERR_FILENO);
    perror((data->av)[data->ac - 1]);
		ft_handle_exit(data, 2);
	}
	ft_change_fd(data, data->out, STDOUT_FILENO);
	data->out = -1;
	close((data->fd)[1]);
}
