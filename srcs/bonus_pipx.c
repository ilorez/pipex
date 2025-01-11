/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:53:31 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/11 15:27:12 by znajdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pipx.h"
#include "libft.h"

// dup a FD and close it
t_bool  ft_change_fd(int fd, int to)
{
  if (dup2(fd, to) == -1)
  {
    perror("dup2");
    exit(1);
  }
  close(fd);
  return true;
}

// get paths & split it from envp
char **ft_get_paths(char *envp[])
{
  char **paths;
  char *tmp;

  paths = NULL;
  while (envp)
  {
    if (ft_strncmp(*envp, "PATH=", 5) == 0)
    {
      paths = ft_split(*envp, ':');
      break;
    }
    envp++;
  }
  if (!paths)
  {
    // set errno
    ft_printf("error not fonded");
    exit(1);
  }
  tmp = paths[0];
  paths[0] = ft_strdup(tmp+5);
  free(tmp);
  return paths;
}

// get path can be founded
char *ft_get_right_path(char *cmd, char **paths)
{
  char *path;

  path = NULL;
  while (*paths)
  {
    path = ft_strjoin(ft_strjoin(paths[0], "/"), cmd);
    if (access(path, F_OK | X_OK) == 0)
      return path;
    free(path);
    paths++;
  }
  return (ft_strdup(cmd));
}
void ft_close(int fd)
{


}

// main functions
int main(int argc, char *argv[], char *envp[]) 
{
  int fd1[2];
  int infile;
  int outfile;
  char **paths;
  char *path;
  char **cmds;
  int read;
  int pid;

  if (argc <= 5)
  {
    ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
    return EXIT_FAILURE;
  }
  paths = ft_get_paths(envp);

  read = open(argv[1], O_RDONLY);
  if (read == -1)
  {
          perror("open infile");
          exit(1);
  }
  outfile = open(argv[argc-1], O_WRONLY | O_CREAT, 0777);
  if (outfile == -1)
  {
      perror("open outfile");
      exit(1);
  }
  while(i=2, i < argc-1, i++)
  {
    cmds = split(argv[i]);
    path = get_right_path(paths);
    if (pipe(fd1) == -1)
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
    if (pid==0)
    {
        if (i < argc - 2)
          dup2(fd1[1], 1);
        else
        {
          dup2(outfile, 1);
          close(outfile);
        }
        dup2(read, 0);
        close(read);
        close(fd[1]);
        close(fd[0]);
        execve(path, cmds, envp);
    }
    close(fd1[1])
    wait(null);
    read = fd1[0];
    free(cmds);
    free(path);
  }
  
}

