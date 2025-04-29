#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

int main(void)
{
  char *command = NULL;
  bool isInteractive = isatty(STDIN_FILENO);
  int cmd_status;

  while (true)
  {
    print_prompt(isInteractive);
    free(command);
    command = NULL;
    cmd_status = getcmd(&command);

    if (cmd_status == 0)
    {
      if (command == NULL || command[0] == '\0')
      {
        continue;
      }
      printf("Command ok: %s\n", command);
      /*
            TODO: 1. Parse the command into a SimpleCommand struct
            TODO: 2. Check if it's a built-in command
            TODO: 3. If not built-in, fork child process and execute command
      */
    }
    else if (cmd_status == 1)
    {
      if (isInteractive)
      {
        printf("\n");
      }
      break;
    }
    else
    {
      break;
    }
  }
  free(command);
  return (EXIT_SUCCESS);
}