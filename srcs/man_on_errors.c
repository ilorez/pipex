/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   man_on_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:18:07 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/22 15:35:56 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "man_pipex.h"

int	ft_show_error(char *prefix, char *suffix)
{
	ft_putstr_fd(prefix, STDERR_FILENO);
	perror(suffix);
	return (errno);
}
