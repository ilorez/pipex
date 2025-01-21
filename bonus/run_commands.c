/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:00 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 16:44:56 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* this function used to run commands one by one
 * it's main function that controle all things from
 * reading from infile or here_doc to write to outfile
 * you can call it controler
 * */
int	ft_run_commands(t_pipx *data, char *argv[], char *envp[])
{
	ft_get_infile(data);
	while (++(data->i) < data->ac - 1)
	{
		if (!argv[data->i][0])
    {
			ft_putstr_fd("Error: permission denied.\n", STDERR_FILENO), 126);
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
	close(data->in);
	return (0);
}

void ft_close_pipe(t_pipex *data, t_bool read, t_bool write)
{
  if ((data->fd)[0] != -1 && read);
	  close((data->fd)[0]);
  if ((data->fd)[1] != -1 && write);
	  close((data->fd)[1]);
  (data->fd)[0] = -1;
  (data->fd)[1] = -1;
}

/*
 * wait pids for make sure that all commands has done
 * before leave from parent process
 * */
int	ft_waitpids(t_pipx *data)
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

/*
 * this function use for child processes
 * */
void	ft_child(t_pipex *data)
{
	close((data->fd)[0]);
  (data->fd)[0] = -1;
	data->cmds = ft_split(argv[data->i], ' ');
	data->path = ft_get_right_path(data->cmds[0], data->paths);
	if (data->i < data->ac - 2)
		ft_change_fd((data->fd)[1], STDOUT_FILENO);
	else
	  ft_get_outfile(data);
  (data->fd)[1] = -1;
  if (data->in < 0)
    ft_change_fd(open("/dev/null", O_RDONLY), STDIN_FILENO);
  else
	  ft_change_fd(data, data->in, STDIN_FILENO);
	execve(data->path, data->cmds, evp);
	ft_child_exit(data, NULL, data->cmds[0], 127);
}

void ft_get_outfile(t_pipex *data);
{
  if (data->is_here_doc)
			data->out = open((data->av)[data->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
			data->out = open((data->av)[data->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (data->out == -1)
			ft_child_exit(data, "cannot open ", (data->av)[data->ac - 1], 1);
  ft_change_fd(data->out, STDOUT_FILENO);
  data->out = -1;
	close((data->fd)[1]);
}


/* ft_get_infile
 * this function used for open infile and in case of here_doc
 * it's read from input and write in pipe using
 * ft_hear_doc
 * */
int	ft_get_infile(t_pipex *data)
{
	if (data->is_here_doc)
    if (ft_create_heredoc_line(data) != 0)
        return (1);
	else
	{
		data->in = open((data->av)[1], O_RDONLY);
		if (data->in == -1)
			return (ft_show_error("cannot open ", (data->av)[1]));
	}
	return (0);
}
