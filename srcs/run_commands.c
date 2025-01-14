/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:00 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/14 10:57:00 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

t_bool	ft_run_commands(t_pipx *data, char *argv[], char *envp[], char *paths[])
{
	if (ft_open_rw_files(&data, argv, argc) == false)
		return (false);
	while (++(data->i) < data->argc - 1)
	{
		data->cmds = ft_split(argv[data->i], ' ');
		data->path = ft_get_right_path(data->cmds[0], paths);
		if (pipe(data->fd) == -1)
			return (ft_on_error(data, data->cmds, data->path, "pipe"));
		data->pid = fork();
		if (data->pid == -1)
			return (ft_on_error(data, data->cmds, data->path, "fork"));
		else if (data->pid == 0)
			ft_child(data, envp);
		close((data->fd)[1]);
		data->infile = (data->fd)[0];
		ft_on_error(data, data->cmds, data->path, NULL);
	}
	close(data->infile);
	wait(NULL);
	return (true);
}

void	ft_child(t_pipx *data, char *envp[])
{
	if (data->i < data->argc - 2)
		ft_change_fd((data->fd)[1], STDOUT_FILENO);
	else
  {
		ft_change_fd(data->outfile, STDOUT_FILENO);
	  close((data->fd)[1]);
  }
	ft_change_fd(data->infile, STDIN_FILENO);
	close((data->fd)[0]);
	if (execve(data->path, data->cmds, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
}

voiv ft_read_from_input(t_pipx *data, char *av[])
{
  char *line;
  
  close(fd[0]);
  line = ft_get_next_line(STDIN_FILENO);
  while(line && ft_strncmp(av[2], line, ft_strlen(av[2]) + 1) != 0)
  {
    write(data->fd[1], line, ft_strlen(line));
    free(line);
    line = ft_get_next_line(STDIN_FILENO);
  }
  free(line);
  close(fd[1]);
  exit(0);
}

t_bool	ft_open_rw_files(t_pipx **data, char *argv[])
{
	if ((*data)->i == 2)
  {
	  (*data)->outfile = open(argv[*data->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
    if (pipe(data->fd) == -1)
			return (ft_on_error(*data, NULL, NULL, "pipe"));
    *data->pid = fork();
		if ((*data)->pid == -1)
			return (ft_on_error(*data, NULL, NULL, "fork"));
		else if ((*data)->pid == 0)
			ft_read_from_input(*data, argv);
		close(((*data)->fd)[1]);
		*data->infile = ((*data)->fd)[0];
  }
  else
  {
  	(*data)->infile = open(argv[1], O_RDONLY);
    if ((*data)->infile == -1)
  	  return (ft_on_error((*data), NULL, NULL, "open infile"));
  	(*data)->outfile = open(argv[data->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
  }
	if ((*data)->outfile == -1)
		return (ft_on_error(*data, NULL, NULL, "open outfile"));
	return (true);
}

