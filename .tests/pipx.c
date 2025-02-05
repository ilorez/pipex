/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znajdaou <znajdaou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:32:17 by znajdaou          #+#    #+#             */
/*   Updated: 2025/01/09 12:04:59 by znajdaou         ###   ########.fr       */
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
      paths = ft_split(((*envp)+5), ':');
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

// main functions
int main(int argc, char *argv[], char *envp[]) 
{
  int pid;
  int fd[2];
  int infile;
  char **cmds;
  int outfile;
  char **paths;
  char *path;
  t_list *bl_lst;

  if (argc != 5)
  {
    ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
    return EXIT_FAILURE;
  }
   
  paths = ft_ad(ft_get_paths(envp), &bl_lst, 1, ft_free_str_lst);
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
    close(fd[0]);
    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
    {
          perror("open infile");
          exit(1);
    }
    ft_change_fd(infile, STDIN_FILENO);
    ft_change_fd(fd[1], STDOUT_FILENO);
    cmds = ft_split(argv[2], ' ');
    path = ft_get_right_path(cmds[0], paths);
    if(execve(path, cmds, envp) == -1)
    {
      perror("execve cmd1");
      free(path);
      ft_free_str_lst(cmds);
      exit(1);
    }
  }
  close(fd[1]);
  wait(NULL);
  if (fork() == 0)
  {
    outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
    if (outfile == -1)
    {
        perror("open outfile");
        exit(1);
    }
    ft_change_fd(fd[0], STDIN_FILENO);
    ft_change_fd(outfile, STDOUT_FILENO);
    cmds = ft_split(argv[3], ' ');
    path = ft_get_right_path(cmds[0], paths);
    if(execve(path, cmds, envp) == -1)
    {
      perror("execve cmd2");
      ft_free_str_lst(cmds);
      exit(1);
    }
  }
  wait(NULL);
  return EXIT_SUCCESS;
}

