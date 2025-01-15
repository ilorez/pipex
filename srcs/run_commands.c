/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:00 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/15 16:32:55 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_run_commands(t_pipx *data, char *argv[], char *envp[])
{
	if (ft_open_rw_files(&data, argv))
		return (1);
	while (++(data->i) < data->argc - 1)
	{
		if (pipe(data->fd) == -1)
			return (ft_on_error(NULL, NULL, "pipe"));
		data->pid = fork();
		if (data->pid == -1)
			return (ft_on_error(NULL, NULL, "fork"));
		else if (data->pid == 0)
			ft_child(data, envp, argv);
		close((data->fd)[1]);
		data->infile = (data->fd)[0];
	}
	close(data->infile);
	wait(NULL);
	return (0);
}

void	ft_child(t_pipx *data, char *envp[], char **argv)
{
	data->cmds = ft_split(argv[data->i], ' ');
	data->path = ft_get_right_path(data->cmds[0], data->paths);
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
		ft_on_error(data->cmds, data->path, "execve");
		ft_free_data(data);
		exit(errno);
	}
}

void	ft_read_from_input(t_pipx *data, char *av[])
{
	char	*line;
	size_t	hd_s;
	size_t	line_s;

	close((data->fd)[0]);
	ft_putstr_fd("here_doc> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	hd_s = ft_strlen(av[2]);
	line_s = ft_strlen(line) - 1;
	while (line && !(ft_strncmp(av[2], line, hd_s) == 0 && line_s == hd_s))
	{
		ft_putstr_fd(line, (data->fd)[1]);
		free(line);
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		line_s = ft_strlen(line) - 1;
	}
	free(line);
	close((data->fd)[1]);
	ft_free_data(data);
	exit(0);
}

int	ft_open_rw_files(t_pipx **data, char *argv[])
{
	if ((*data)->i == 2)
	{
		(*data)->outfile = open(argv[(*data)->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (pipe((*data)->fd) == -1)
			return (ft_on_error(NULL, NULL, "pipe"));
		(*data)->pid = fork();
		if ((*data)->pid == -1)
			return (ft_on_error(NULL, NULL, "fork"));
		else if ((*data)->pid == 0)
			ft_read_from_input(*data, argv);
		close(((*data)->fd)[1]);
		(*data)->infile = ((*data)->fd)[0];
	}
	else
	{
		(*data)->infile = open(argv[1], O_RDONLY);
		if ((*data)->infile == -1)
			return (ft_on_error(NULL, NULL, "open infile"));
		(*data)->outfile = open(argv[(*data)->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
	if ((*data)->outfile == -1)
		return (ft_on_error(NULL, NULL, "open outfile"));
	return (0);
}
