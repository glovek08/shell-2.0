#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stddef.h>

// MACROS
#define MAX_BUFFER_SIZE 1024
#define MAX_ARGS 10 // As stated in project description.
#define PROMPT "8===D "

typedef struct Command
{
  char *cmd_id;             // From PATH /usr/bin/ls
  char *args[MAX_ARGS + 1]; // -a -v
  int arg_count;            // 2
} cmd;

// ***** PROTOTYPE REALM ******
void print_prompt(bool);
int get_cmd(char **command_ptr);
struct Command parse_command(char *input_line);

#endif /* MAIN_H */