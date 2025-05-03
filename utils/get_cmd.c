#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

/**
 * get_cmd - Reads a line of input from stdin.
 * @command_ptr: Address of a char pointer to store the allocated command string.
 *
 * Return:
 *  0: Success, command read into *command_ptr.
 *  1: EOF reached. *command_ptr might be NULL or contain previous buffer.
 * -1: Error reading input. *command_ptr might be NULL or contain previous buffer.
 */
int get_cmd(char **command_ptr)
{
  char *buffer = NULL;
  size_t buffer_size = 5;
  ssize_t bytes_read = 0;

  bytes_read = getline(&buffer, &buffer_size, stdin);
  if (bytes_read == -1)
  {
    if (feof(stdin))
    {
      free(buffer);
      printf("*** GOODBYE! ***\n");
      *command_ptr = NULL;
      return (1);
    }
    else
    {
      perror("getline");
      free(buffer);
      *command_ptr = NULL;
      return (-1);
    }
  }
  if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
  {
    buffer[bytes_read - 1] = '\0';
  }
  *command_ptr = buffer;
  return (0);
}