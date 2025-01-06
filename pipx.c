/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:32:17 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/06 14:29:39 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int int main(int argc, char *argv[], char *envp[]) 
{
  int pid;
  int fd[2];
  int fd1;
  int fd2;
  char *line;
  char *f_v;
  
  if (pipe(fd) == -1)
  {
    perror("pipe");
    return EXIT_FAILURE;
  }
  pid = fork();
  if (pid == -1)
  {
    perror("fork");
    return EXIT_FAILURE;
  }
  if (pid == 0)
  {
    fd1 = open(argv[1], O_RONLY);
    line = get_next_line(fd1);
    while(line)
    {
      ft_strjoin(f_v, line);

      free(line);
      line = get_next_line(fd1);
    }
    free(line;)


    


  }

  return EXIT_SUCCESS;
}


