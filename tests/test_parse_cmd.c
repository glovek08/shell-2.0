#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For exit

// Helper function to print command details
void print_parsed_cmd_details(const cmd *p_cmd, const char *test_case_name)
{
  printf("--- Test Case: %s ---\n", test_case_name);
  if (p_cmd->args == NULL && p_cmd->arg_count == 0 && p_cmd->input_file == NULL && p_cmd->output_file == NULL)
  {
    printf("Command parsing resulted in an empty/error state as expected for this case.\n");
    return;
  }

  printf("Command ID (first arg): %s\n", (p_cmd->arg_count > 0 && p_cmd->args[0]) ? p_cmd->args[0] : "N/A");
  printf("Arguments (count: %d):\n", p_cmd->arg_count);
  for (int i = 0; i < p_cmd->arg_count; i++)
  {
    printf("  args[%d]: %s\n", i, p_cmd->args[i]);
  }
  if (p_cmd->args && p_cmd->args[p_cmd->arg_count] == NULL)
  {
    printf("  args[%d]: NULL (correctly terminated)\n", p_cmd->arg_count);
  }
  else if (p_cmd->args)
  {
    printf("  args list not NULL terminated properly.\n");
  }

  printf("Input File: %s\n", p_cmd->input_file ? p_cmd->input_file : "N/A");
  printf("Output File: %s\n", p_cmd->output_file ? p_cmd->output_file : "N/A");
  printf("-------------------------\n\n");
}

int main()
{
  cmd parsed;

  // Test Case 1: Simple command
  const char *tc1_str = "ls -l /tmp";
  parsed = parse_command(tc1_str);
  print_parsed_cmd_details(&parsed, "Simple Command");
  free_parsed_command(&parsed);

  // Test Case 2: Command with input redirection
  const char *tc2_str = "grep pattern < input.txt";
  parsed = parse_command(tc2_str);
  print_parsed_cmd_details(&parsed, "Input Redirection");
  free_parsed_command(&parsed);

  // Test Case 3: Command with output redirection
  const char *tc3_str = "cat > output.log";
  parsed = parse_command(tc3_str);
  print_parsed_cmd_details(&parsed, "Output Redirection");
  free_parsed_command(&parsed);

  // Test Case 4: Command with both input and output redirection
  const char *tc4_str = "sort < data.in > data.out";
  parsed = parse_command(tc4_str);
  print_parsed_cmd_details(&parsed, "Both Redirections");
  free_parsed_command(&parsed);

  // Test Case 5: Command with arguments after output redirection
  const char *tc5_str = "wc -l > count.txt < somefile.txt"; // Order matters for simple parser
  parsed = parse_command(tc5_str);
  print_parsed_cmd_details(&parsed, "Args after Output Redirection (then input)");
  free_parsed_command(&parsed);

  // Test Case 6: Only command
  const char *tc6_str = "execute";
  parsed = parse_command(tc6_str);
  print_parsed_cmd_details(&parsed, "Only Command");
  free_parsed_command(&parsed);

  // Test Case 7: Empty string
  const char *tc7_str = "";
  parsed = parse_command(tc7_str);
  print_parsed_cmd_details(&parsed, "Empty String");
  free_parsed_command(&parsed);

  // Test Case 8: String with only spaces
  const char *tc8_str = "   ";
  parsed = parse_command(tc8_str);
  print_parsed_cmd_details(&parsed, "Only Spaces");
  free_parsed_command(&parsed);

  // Test Case 9: Max arguments
  char tc9_str[MAX_BUFFER_SIZE] = "cmd";
  for (int i = 0; i < MAX_ARGS - 1; i++)
  { // cmd + (MAX_ARGS - 1) args
    char arg_buf[10];
    sprintf(arg_buf, " arg%d", i);
    strcat(tc9_str, arg_buf);
  }
  parsed = parse_command(tc9_str);
  print_parsed_cmd_details(&parsed, "Max Arguments");
  free_parsed_command(&parsed);

  // Test Case 10: Too many arguments
  char tc10_str[MAX_BUFFER_SIZE] = "cmd";
  for (int i = 0; i < MAX_ARGS + 5; i++)
  { // cmd + (MAX_ARGS + 5) args
    char arg_buf[10];
    sprintf(arg_buf, " arg%d", i);
    strcat(tc10_str, arg_buf);
  }
  parsed = parse_command(tc10_str);
  print_parsed_cmd_details(&parsed, "Too Many Arguments");
  free_parsed_command(&parsed);

  // Test Case 11: Input redirection missing filename
  const char *tc11_str = "grep test <";
  parsed = parse_command(tc11_str);
  print_parsed_cmd_details(&parsed, "Input Redirection Missing Filename");
  // Note: parse_command should handle this error and return a cmd struct
  // where args might be NULL or arg_count is 0.
  // The free_parsed_command should still be safe to call.
  free_parsed_command(&parsed);

  // Test Case 12: Output redirection missing filename
  const char *tc12_str = "cat > ";
  parsed = parse_command(tc12_str);
  print_parsed_cmd_details(&parsed, "Output Redirection Missing Filename");
  free_parsed_command(&parsed);

  // Test Case 13: Multiple redirections (behavior might depend on parser logic for duplicates)
  const char *tc13_str = "cmd < in1.txt < in2.txt > out1.txt > out2.txt";
  parsed = parse_command(tc13_str);
  print_parsed_cmd_details(&parsed, "Multiple Redirections");
  free_parsed_command(&parsed);

  // Test Case 14: Redirection symbols without spaces
  const char *tc14_str = "cmd<input.txt>output.txt";
  parsed = parse_command(tc14_str);
  print_parsed_cmd_details(&parsed, "Redirection symbols without spaces (depends on strtok)");
  free_parsed_command(&parsed);

  printf("All tests completed.\n");
  return 0;
}
