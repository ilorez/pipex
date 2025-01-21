/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:00 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 17:47:29 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* this function used to run commands one by one
 * it's main function that controle all things from
 * reading from infile or here_doc to write to outfile
 * you can call it controler
 * */
int	ft_run_commands(t_pipex *data)
{
	ft_get_infile(data);
	while (++(data->i) < data->ac - 1)
	{
		if (!(data->av)[data->i][0])
    {
			ft_putstr_fd("Error: permission denied.\n", STDERR_FILENO);
      data->status = 126;
      continue;
    }
		if (pipe(data->fd) == -1)
			return (ft_show_error(NULL, "pipe"));
		(data->pids)[data->j] = fork();
		if ((data->pids)[data->j] == -1)
			return (ft_show_error(NULL, "fork"));
		else if ((data->pids)[data->j] == 0)
			ft_child(data);
		close(data->in);
		data->in = (data->fd)[0];
    ft_close_pipe(data, false, true);
		(data->j)++;
	}
	if (ft_waitpids(data))
		return (data->status);
	return (0);
}

/* ft_get_infile
 * this function used for open infile and in case of here_doc
 * it's read from input and write in pipe using
 * ft_hear_doc
 * */
int	ft_get_infile(t_pipex *data)
{
	if (data->is_here_doc)
  {
    if (ft_create_heredoc_line(data) != 0)
        return (1);
  }
	else
	{
		data->in = open((data->av)[1], O_RDONLY);
		if (data->in == -1)
			return (ft_show_error("cannot open ", (data->av)[1]));
	}
	return (0);
}

/*
 * wait pids for make sure that all commands has done
 * before leave from parent process
 * */
int	ft_waitpids(t_pipex *data)
{
	int	i;

	i = -1;
	while ((data->pids)[++i])
	{
		waitpid((data->pids)[i], &(data->status), 0);
		if (ft_wifexited(data->status))
			data->status = ft_wexitstatus(data->status);
    else 
      data->status = 0;
	}
	return (data->status);
}
