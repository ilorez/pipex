/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:32:50 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/17 17:45:28 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

	if (!envp)
		return (NULL);
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
		ft_putstr_fd("Error: could not found paths\n", STDERR_FILENO);
		return (NULL);
	}
	return (paths);
}

// get path can be founded
char	*ft_get_right_path(char *cmd, char **paths)
{
	char	*path;

	if (cmd[0] == '/' || !ft_strncmp(cmd, "../", 3) || !ft_strncmp(cmd, "./",
			2))
		return (ft_strdup(cmd));
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

void	ft_free_data(t_pipx *data)
{
	if (!data)
		return ;
	if (data->paths)
		ft_free_str_lst(data->paths);
	if (data->pids)
		free(data->pids);
	free(data);
}
