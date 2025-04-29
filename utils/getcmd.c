#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

char *getcmd()
{
  char *buffer = NULL;
  size_t buffer_size = 0;
  ssize_t bytes_read = 0;

  bytes_read = getline(&buffer, &buffer_size, stdin);
  if (bytes_read == -1)
  {
    if (feof(STDIN_FILENO))
    {
      free(buffer);
      printf("EoF reached.\n");
      exit(EXIT_SUCCESS);
    }
    else
    {
      perror("getline");
      fprintf(stderr, "Couldn't read command.\n");
      free(buffer);
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    if (bytes_read > 0 && buffer[bytes_read - 1] == '\n')
    {
      buffer[bytes_read - 1] = '\0';
      bytes_read--;
    }
    printf("Command is: %s\n", buffer);
    return (buffer);
    // parse command.
  }
}