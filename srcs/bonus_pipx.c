/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/12 13:25:17 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipx.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_pipx
{
	int		fd[2];
	int		pid;
	int		outfile;
	int		infile;
	int		i;
	char	*path;
	char	**cmds;
}			t_pipx;

// dup a FD and close it
t_bool	ft_change_fd(int fd, int to)
{
	if (dup2(fd, to) == -1)
		return (false);
	close(fd);
	return (true);
}

// get paths & split it from envp
char	**ft_get_paths(char *envp[])
{
	char	**paths;

	paths = NULL;
	while (envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			paths = ft_split((*envp + 5), ':');
			break ;
		}
		envp++;
	}
	if (!paths)
	{
		write(2, "Error: could not found paths\n", 29);
		exit(1);
	}
	return (paths);
}

// get path can be founded
char	*ft_get_right_path(char *cmd, char **paths)
{
	char	*path;

	path = NULL;
	while (*paths)
	{
		path = ft_strjoin(paths[0], cmd, "/");
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		paths++;
	}
	return (ft_strdup(cmd));
}

t_bool	ft_on_error(t_pipx *data, char **cmds, char *path, char *err_msg)
{
	if (cmds)
		ft_free_str_lst(cmds);
	if (path)
		free(path);
	if (err_msg)
	{
		if (data)
			free(data);
		perror(err_msg);
		return (false);
	}
	return (true);
}

void	ft_child(t_pipx *data, int i, int argc, char *envp[])
{
	if (i < argc - 2)
		ft_change_fd((data->fd)[1], 1);
	else
		ft_change_fd(data->outfile, 1);
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
		wait(NULL);
		if (data->i < argc - 2)
			data->infile = (data->fd)[0];
		else
			close((data->fd)[0]);
		ft_on_error(data, data->cmds, data->path, NULL);
	}
	return (true);
}

// main functions
int	main(int argc, char *argv[], char *envp[])
{
	char	**paths;

	if (argc < 5)
	{
		ft_printf("Usage: \n\t%s infile cmd1 cmd2 ... cmdn outfile\n", argv[0]);
		return (EXIT_FAILURE);
	}
	paths = ft_get_paths(envp);
	if (!ft_run_commands(argc, argv, envp, paths))
		return (free(paths), EXIT_FAILURE);
	free(paths);
	return (0);
}
