/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:20:29 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/17 16:26:13 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
