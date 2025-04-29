#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

void print_prompt(bool isInteractive)
{
  if (isInteractive)
  {
    write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
  }
}