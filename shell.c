#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
/**
 * main - Entry point.
 *
 * Return: Always EXIT_SUCCESS
 */
int main(void)
{
  char *command = NULL;
  bool isInteractive = isatty(STDIN_FILENO);
  int cmd_status;
  cmd parsed_cmd;

  while (true)
  {
    print_prompt(isInteractive);
    free(command);
    command = NULL;
    cmd_status = get_cmd(&command);

    if (cmd_status == 0)
    {
      if (command == NULL || command[0] == '\0')
        continue;
      parsed_cmd = parse_command(command);

      if (parsed_cmd.arg_count == 0)
        continue;

      exec_cmd(parsed_cmd);

      // TODO: 1. Check if it's a built-in command (e.g., exit, env)
      // TODO: 2. If not built-in, fork child process and execute command
      // I completely ignored TODO 1 sorry Polo.
    }
    else if (cmd_status == 1)
    {
      if (isInteractive)
        printf("\n");
      break;
    }
    else
      break;
  }
  free(command);
  return (EXIT_SUCCESS);
}