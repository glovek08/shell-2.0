#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stddef.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARGS 10 // As stated in project description.
#define PROMPT "8===D "

typedef struct Command
{
  char *command_path;
  char *args[MAX_ARGS + 1];
  int arg_count;
} cmd;

void print_prompt(bool);
int getcmd(char **command_ptr);
cmd parse_command(char *line);

#endif /* MAIN_H */