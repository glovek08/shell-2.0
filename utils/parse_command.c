#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * parse_command - parses a command line string into a cmd struct.
 * @input_line: The command line string to parse.
 *
 * Return: @input_line parsed into a @new_command struct with command's name, path and
 *    arguments as attributes.
 */
cmd parse_command(char *input_line)
{
  char delims[] = " \t\n\r\a";
  char *token = NULL;
  cmd new_command;
  int i = 0, j = 0;

  new_command.cmd_id = NULL;
  new_command.arg_count = 0;

  for (; j <= MAX_ARGS; j++)
    new_command.args[j] = NULL;
  if (input_line == NULL)
    return (new_command);

  for (token = strtok(input_line, delims); token != NULL && i < MAX_ARGS; token = strtok(NULL, delims))
  {
    new_command.args[i] = token;
    i++;
  }

  new_command.arg_count = i;
  if (new_command.arg_count > 0)
    new_command.cmd_id = new_command.args[0];

  // ******** DEBUG STUFF *********
  printf("Command Parsed...\n");
  printf("Cmd ID: %s\n", new_command.cmd_id ? new_command.cmd_id : "(null)");
  printf("Cmd Arguments: ");
  for (int k = 0; k < new_command.arg_count; k++)
    printf("[%s] ", new_command.args[k]);
  printf("\n");
  printf("Cmd Args Counter: %i\n", new_command.arg_count);

  return (new_command);
}
