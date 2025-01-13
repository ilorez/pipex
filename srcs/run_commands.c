/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:00 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/13 14:47:14 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

void	ft_child(t_pipx *data, int i, int argc, char *envp[])
{
	if (i < argc - 2)
		ft_change_fd((data->fd)[1], 1);
	else
  {
		ft_change_fd(data->outfile, 1);
	  close((data->fd)[1]);
  }
	ft_change_fd(data->infile, 0);
	close((data->fd)[0]);
	if (execve(data->path, data->cmds, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

t_bool	ft_open_rw_files(t_pipx **data, char *argv[], int argc)
{
	*data = ft_calloc(sizeof(t_pipx), 1);
	(*data)->i = 1;
	(*data)->infile = open(argv[1], O_RDONLY);
	if ((*data)->infile == -1)
		return (ft_on_error((*data), NULL, NULL, "open infile"));
	(*data)->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
	if ((*data)->outfile == -1)
		return (ft_on_error(*data, NULL, NULL, "open outfile"));
	return (true);
}

t_bool	ft_run_commands(int argc, char *argv[], char *envp[], char *paths[])
{
	t_pipx	*data;

	if (ft_open_rw_files(&data, argv, argc) == false)
		return (false);
	while (++(data->i) < argc - 1)
	{
		data->cmds = ft_split(argv[data->i], ' ');
		data->path = ft_get_right_path(data->cmds[0], paths);
		if (pipe(data->fd) == -1)
			return (ft_on_error(data, data->cmds, data->path, "pipe"));
		data->pid = fork();
		if (data->pid == -1)
			return (ft_on_error(data, data->cmds, data->path, "fork"));
		else if (data->pid == 0)
			ft_child(data, data->i, argc, envp);
		close((data->fd)[1]);
		data->infile = (data->fd)[0];
		ft_on_error(data, data->cmds, data->path, NULL);
	}
	close(data->infile);
	wait(NULL);
	return (true);
}
