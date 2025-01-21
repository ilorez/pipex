/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:04:17 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 12:43:28 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_handle_exit(t_pipex *data, int status)
{
  if (!data)
    return (0);
  if ((data->fd)[0] != -1)
    close((data->fd)[0]);
  if ((data->fd)[1] != -1)
    close((data->fd)[1]);
  if (data->in != -1)
    close(data->in);
  if (data->out != -1)
    close(data->out);
  if (data->pids)
    free(data->pids);
  if (data->path)
    free(data->path);
  if (data->cmds)
    ft_free_str(data->cmds);
  if (data->paths)
    ft_free_str(data->paths);
  if (data->is_here_doc && data->tmpfile)
    free(data->tmpfile)
  if (data)
    free(data);
  exit(status);
}
