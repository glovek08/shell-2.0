#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
  char *command;
  bool isInteractive = isatty(STDIN_FILENO);
  // print one time only, on shell startup a welcoming message.
  while (true)
  {
    print_prompt(isInteractive);
    command = getcmd(); // REMEMBER TO FREE BUFFER FOR CMD!!!!
    printf("Command is: %s\n", command);
    free(command);
  }
  return (EXIT_SUCCESS);
}
