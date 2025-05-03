#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * Return: 1 nothing to execute, 0 everything OK, -1 error.
 */
int exec_cmd(cmd parsed_command)
{
  if (!parsed_command.args[0])
    return (1);

  printf("PID: %i\n", getpid());

  pid_t pid = fork();
  int status;

  printf("Hello, I execute commands \n");
  printf("You've gave me: %s\n", parsed_command.cmd_id);
  printf("PPID: %i\n", getppid());
  printf("PID: %i\n", getpid());

  if (pid == -1)
  {
    perror("fork");
    return (-1);
  }
  else if (pid == 0)
  {
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