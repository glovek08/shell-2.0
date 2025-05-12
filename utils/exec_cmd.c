#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

/**
 * Return: 1 nothing to execute, 0 everything OK, -1 error.
 */
int exec_cmd(cmd parsed_command)
{
  if (!parsed_command.args[0])
    return (1);

  pid_t pid = fork();
  int status;

  if (pid == -1)
  {
    perror("fork");
    return (-1);
  }
  else if (pid == 0)
  {
    if (parsed_command.input_file != NULL)
    {
      int fd_in = open(parsed_command.input_file, O_RDONLY);
      if (fd_in == -1)
      {
        perror(parsed_command.input_file);
        exit(1);
      }
      if (dup2(fd_in, STDIN_FILENO) == -1)
      {
        perror("dup2 input");
        close(fd_in);
        exit(1);
      }
      close(fd_in);
    }
    if (parsed_command.output_file != NULL)
    {
      int fd_out = open(parsed_command.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd_out == -1)
      {
        perror(parsed_command.output_file);
        exit(1);
      }
      if (dup2(fd_out, STDOUT_FILENO) == -1)
      {
        perror("dup2 output");
        close(fd_out);
        exit(1);
      }
      close(fd_out);
    }

    if (execvp(parsed_command.cmd_id, parsed_command.args) == -1)
    {
      fprintf(stderr, "./shell: 1: %s: not found\n", parsed_command.args[0]);
      exit(127);
    }
  }
  else if (pid > 0)
  {
    for (;;)
    {
      if (waitpid(pid, &status, 0) == -1)
      {
        if (errno != EINTR)
        {
          perror("waitpid");
          return (-1);
        }
      }
      if (WIFEXITED(status) || WIFSIGNALED(status))
        break;
    }
  }
  return (0);
}