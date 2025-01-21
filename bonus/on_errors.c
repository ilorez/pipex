/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:07 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/21 18:50:32 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_show_error(char *prefix, char *suffix)
{
	ft_putstr_fd(prefix, STDERR_FILENO);
	perror(suffix);
	return (errno);
}
