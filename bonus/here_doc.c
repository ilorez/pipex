/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:20:29 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 18:08:24 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_create_heredoc_line(t_pipex  *data)
{
  int pid;

  data->tmpfile = ft_randtmp_file();
	pid = fork();
	if (pid == -1)
		return (ft_show_error(NULL, "fork"));
	else if (pid == 0)
	{
    (data->fd)[1] = open(data->tmpfile, O_WRONLY | O_CREAT, 0777);
    if ((data->fd)[1] < 0)
    {
        perror("open failed");
        ft_handle_exit(data, 1);
    }
		ft_here_doc((data->fd)[1], (data->av)[2]);
    ft_handle_exit(data, 0);
	}
  waitpid(pid, &(data->status), 0);
	if (ft_wifexited(data->status))
		data->status = ft_wexitstatus(data->status);
  data->in = open(data->tmpfile, O_CREAT | O_RDONLY , 0777);
  if (data->in < 0)
      perror("open failed");
  return (0);
}

char *ft_randtmp_file()
{
  char *tmpfile;
  char *tmp;

  tmpfile = ft_itoa((unsigned long)(&tmpfile));
  if (!tmpfile)
    return (NULL);
  tmp = tmpfile;
  tmpfile = ft_strjoin("/tmp", tmpfile, "/ilorez_herdoc_");
  free(tmp);
  return tmpfile;
}

void	ft_here_doc(int fd, char *eof)
{
	char	*line;
	size_t	hd_s;
	size_t	line_s;

	ft_putstr_fd("here_doc> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	hd_s = ft_strlen(eof);
	line_s = ft_strlen(line) - 1;
	while (line && !(ft_strncmp(eof, line, hd_s) == 0 && line_s == hd_s))
	{
		ft_putstr_fd(line, fd);
		free(line);
		ft_putstr_fd("here_doc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		line_s = ft_strlen(line) - 1;
	}
	free(line);
	close(fd);
}
