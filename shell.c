#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
/**
 * main - Entry point.
 * @argc: argument counter
 * @argv: argument vector
 *
 * Return: Always EXIT_SUCCESS
 */
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
    cmd_status = get_cmd(&command); // que onda el ampersand

    if (cmd_status == 0)
    {
      if (command == NULL || command[0] == '\0')
        continue;
      printf("Command ok: %s\n", command);
      parse_command(command);
      /*
            TODO: 1. Check if it's a built-in command
            TODO: 2. If not built-in, fork child process and execute command
      */
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