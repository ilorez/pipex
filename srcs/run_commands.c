/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:33:00 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/17 18:55:18 by znajdaou         ###   ########.fr       */
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
	ft_get_infile(data, argv);
	while (++(data->i) < data->argc - 1)
	{
		if (!argv[data->i][0])
			return (ft_putstr_fd("Error: Not valid command\n", STDERR_FILENO),
				1);
		if (pipe(data->fd) == -1)
			return (ft_on_error(NULL, NULL, "pipe"));
		(data->pids)[data->j] = fork();
		if ((data->pids)[data->j] == -1)
			return (ft_on_error(NULL, NULL, "fork"));
		else if ((data->pids)[data->j] == 0)
			ft_child(data, envp, argv);
		close((data->fd)[1]);
		close(data->infile);
		data->infile = (data->fd)[0];
		(data->j)++;
	}
	if (ft_waitpids(data))
		return (data->status);
	close(data->infile);
	return (0);
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
	}
	return (data->status);
}

/*
 * this function use for child processes
 * */
void	ft_child(t_pipx *data, char *envp[], char **argv)
{
	close((data->fd)[0]);
	data->cmds = ft_split(argv[data->i], ' ');
	data->path = ft_get_right_path(data->cmds[0], data->paths);
	if (data->i < data->argc - 2)
		ft_change_fd((data->fd)[1], STDOUT_FILENO);
	else
	{
		if (data->is_here_doc)
			data->outfile = open(argv[data->argc - 1],
					O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			data->outfile = open(argv[data->argc - 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (data->outfile == -1)
			ft_child_exit(data, "field to open outfile");
		ft_change_fd(data->outfile, STDOUT_FILENO);
		close((data->fd)[1]);
	}
	if (data->infile >= 0)
		ft_change_fd(data->infile, STDIN_FILENO);
	else
		close(0);
	execve(data->path, data->cmds, envp);
	ft_child_exit(data, "execve");
}

/* ft_get_infile
 * this function used for open infile and in case of here_doc
 * it's read from input and write in pipe using
 * ft_hear_doc
 * */
int	ft_get_infile(t_pipx *data, char *argv[])
{
	if (data->is_here_doc)
	{
		if (pipe(data->fd) == -1)
			return (ft_on_error(NULL, NULL, "pipe"));
		(data->pids)[data->j] = fork();
		if ((data->pids)[data->j] == -1)
			return (ft_on_error(NULL, NULL, "fork"));
		else if ((data->pids)[data->j] == 0)
		{
			close((data->fd)[0]);
			ft_here_doc((data->fd)[1], argv[2]);
			ft_free_data(data);
			exit(0);
		}
		close((data->fd)[1]);
		data->infile = (data->fd)[0];
		(data->j)++;
	}
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile == -1)
			return (ft_on_error(NULL, NULL, "open infile"));
	}
	return (0);
}
