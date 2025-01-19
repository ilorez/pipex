/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:07 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/19 10:09:57 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_exit(t_pipx *data, char *err_msg, int e_s)
{
	ft_on_error(data->cmds, data->path, err_msg);
	ft_free_data(data);
	exit(e_s);
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

/*
int ft_handle_error(t_pipx *data, char *err, int exit_status)
{
  if (data->cmds)
		ft_free_str_lst(data->cmds);
	if (data->path)
		free(data->path);
  if (err_msg)
	{
		perror(err_msg);
    if (!exit_status)
		  return (errno);
	}
  if (exit_status)
  {
	  ft_free_data(data);
	  exit(exit_status);
  }
  return (0);
}*/
