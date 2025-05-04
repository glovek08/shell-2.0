#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>

extern char **environ;
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
  cmd parsed_command;
  char **temp_env = environ;

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
      parsed_command = parse_command(command);
      if (parsed_command.arg_count == 0)
        continue;
      if (strcmp(parsed_command.args[0], "exit") == 0)
        break;
      else if (strcmp(parsed_command.args[0], "env") == 0)
      {
        while (*temp_env != NULL)
        {
          printf("%s\n", *temp_env);
          temp_env++;
        }
        continue;
      }
      exec_cmd(parsed_command);

      // TODO: posix compliance.
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