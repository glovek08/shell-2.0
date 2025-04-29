#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void print_prompt()
{
  write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}