/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:07 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 16:01:33 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_exit(t_pipx *data, char *pre, char *suf, int e_s)
{
  ft_show_error(pre, suf);
  ft_handle_exit(data, e_s);
}

int	ft_show_error(char *prefix, char *suffix)
{
  ft_putstr_fd(prefix, STDERR_FILENO);
	perror(suffix);
	return (errno);
}


