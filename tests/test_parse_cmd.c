#include "../main.h" // Should declare cmd struct, parse_command, free_parsed_command, MAX_ARGS, MAX_BUFFER_SIZE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Forward declaration if not in main.h, or ensure it's in main.h
void free_parsed_command(cmd *p_cmd);

// Helper function to print command details
void print_parsed_cmd_details(const cmd *p_cmd, const char *test_case_name)
{
  printf("--- Test Case: \"%s\" ---\n", test_case_name);
  if (p_cmd == NULL)
  {
    printf("Error: cmd pointer is NULL.\n");
    printf("-------------------------\n\n");
    return;
  }

  // Check for a state that parse_command might return for empty input or critical errors
  if (p_cmd->arg_count == 0 && p_cmd->args == NULL && p_cmd->input_file == NULL && p_cmd->output_file == NULL)
  {
    printf("Result: Empty/error state (arg_count=0, args=NULL, no redirection files).\n");
    printf("-------------------------\n\n");
    return;
  }

  printf("Command ID (args[0]): %s\n", (p_cmd->arg_count > 0 && p_cmd->args && p_cmd->args[0]) ? p_cmd->args[0] : "N/A");
  printf("Arguments (arg_count: %d):\n", p_cmd->arg_count);

  if (p_cmd->args != NULL)
  {
    for (int i = 0; i < p_cmd->arg_count; i++)
    {
      printf("  args[%d]: \"%s\"\n", i, p_cmd->args[i] ? p_cmd->args[i] : "(null ptr)");
    }
    if (p_cmd->args[p_cmd->arg_count] == NULL)
    {
      printf("  args[%d]: NULL (correctly NULL-terminated array)\n", p_cmd->arg_count);
    }
    else
    {
      printf("  Error: args array not NULL-terminated at index %d.\n", p_cmd->arg_count);
    }
  }
  else
  {
    if (p_cmd->arg_count > 0)
    {
      printf("  Error: args pointer is NULL, but arg_count is %d.\n", p_cmd->arg_count);
    }
    else
    {
      printf("  args array is NULL (consistent with arg_count=0).\n");
    }
  }

  printf("Input File: %s\n", p_cmd->input_file ? p_cmd->input_file : "N/A");
  printf("Output File: %s\n", p_cmd->output_file ? p_cmd->output_file : "N/A");
  printf("-------------------------\n\n");
}

// Dummy free_parsed_command if not available from main.h for compilation.
// Replace with actual implementation or ensure it's linked.
#ifndef free_parsed_command
void free_parsed_command(cmd *p_cmd)
{
  if (!p_cmd)
    return;

  // Free cmd_id if it's allocated
  free(p_cmd->cmd_id);
  p_cmd->cmd_id = NULL;

  if (p_cmd->args) // Though args is an array, this check is more for arg_count
  {
    for (int i = 0; i < p_cmd->arg_count; i++)
    {
      free(p_cmd->args[i]);  // Assuming args[i] are individually allocated
      p_cmd->args[i] = NULL; // Set freed pointer to NULL
    }
    // Do NOT free(p_cmd->args) itself, as it's an array member of the struct.
  }
  free(p_cmd->input_file);  // Assuming input_file is allocated
  free(p_cmd->output_file); // Assuming output_file is allocated

  // Reset fields
  p_cmd->arg_count = 0;
  p_cmd->input_file = NULL;
  p_cmd->output_file = NULL;
}
#endif

int main()
{
  cmd parsed;

  // Test Case 1: Simple command
  parsed = parse_command("ls -l /tmp");
  print_parsed_cmd_details(&parsed, "ls -l /tmp");
  free_parsed_command(&parsed);

  // Test Case 2: Command with input redirection
  parsed = parse_command("grep pattern < input.txt");
  print_parsed_cmd_details(&parsed, "grep pattern < input.txt");
  free_parsed_command(&parsed);

  // Test Case 3: Command with output redirection
  parsed = parse_command("cat > output.log");
  print_parsed_cmd_details(&parsed, "cat > output.log");
  free_parsed_command(&parsed);

  // Test Case 4: Command with both input and output redirection
  parsed = parse_command("sort < data.in > data.out");
  print_parsed_cmd_details(&parsed, "sort < data.in > data.out");
  free_parsed_command(&parsed);

  // Test Case 5: Redirection order swapped
  parsed = parse_command("wc -l > count.txt < somefile.txt");
  print_parsed_cmd_details(&parsed, "wc -l > count.txt < somefile.txt");
  free_parsed_command(&parsed);

  // Test Case 6: Only command
  parsed = parse_command("execute_only");
  print_parsed_cmd_details(&parsed, "execute_only");
  free_parsed_command(&parsed);

  // Test Case 7: Empty string
  parsed = parse_command("");
  print_parsed_cmd_details(&parsed, "Empty String");
  free_parsed_command(&parsed);

  // Test Case 8: String with only spaces
  parsed = parse_command("   ");
  print_parsed_cmd_details(&parsed, "Only Spaces");
  free_parsed_command(&parsed);

  // Test Case 9: Input redirection missing filename
  parsed = parse_command("grep test <");
  print_parsed_cmd_details(&parsed, "grep test < (missing input filename)");
  free_parsed_command(&parsed);

  // Test Case 10: Output redirection missing filename
  parsed = parse_command("cat > ");
  print_parsed_cmd_details(&parsed, "cat > (missing output filename)");
  free_parsed_command(&parsed);

  // Test Case 11: Multiple input redirections (parser should decide: first, last, or error)
  // Assuming last one wins for this test or it's an error.
  parsed = parse_command("cmd < in1.txt < in2.txt");
  print_parsed_cmd_details(&parsed, "cmd < in1.txt < in2.txt");
  free_parsed_command(&parsed);

  // Test Case 12: Multiple output redirections
  parsed = parse_command("cmd > out1.txt > out2.txt");
  print_parsed_cmd_details(&parsed, "cmd > out1.txt > out2.txt");
  free_parsed_command(&parsed);

  // Test Case 13: Redirection symbols without spaces (depends on tokenizer)
  parsed = parse_command("cmd<input.txt>output.txt");
  print_parsed_cmd_details(&parsed, "cmd<input.txt>output.txt (no spaces around < >)");
  free_parsed_command(&parsed);

  // Test Case 14: Command with args before and after redirection
  parsed = parse_command("cmd arg1 < input.txt arg2 > output.txt arg3");
  print_parsed_cmd_details(&parsed, "cmd arg1 < input.txt arg2 > output.txt arg3");
  free_parsed_command(&parsed);

  // Test Case 15: Only input redirection
  parsed = parse_command("< only_input.txt");
  print_parsed_cmd_details(&parsed, "< only_input.txt (no command)");
  free_parsed_command(&parsed);

  // Test Case 16: Only output redirection
  parsed = parse_command("> only_output.txt");
  print_parsed_cmd_details(&parsed, "> only_output.txt (no command)");
  free_parsed_command(&parsed);

  // Test Case 17: Input and output redirection, no command
  parsed = parse_command("< in.txt > out.txt");
  print_parsed_cmd_details(&parsed, "< in.txt > out.txt (no command)");
  free_parsed_command(&parsed);

  // Test Case 18: Filename with special characters (if supported, or to test quoting if implemented)
  // This test assumes simple filenames for now.
  // parsed = parse_command("cmd > \"file with spaces.txt\"");
  // print_parsed_cmd_details(&parsed, "cmd > \"file with spaces.txt\"");
  // free_parsed_command(&parsed);

  // Test Case 19: Command with many arguments (if MAX_ARGS is a factor)
  // char tc_max_args[MAX_BUFFER_SIZE] = "cmd"; // Assuming MAX_BUFFER_SIZE is defined
  // for (int i = 0; i < MAX_ARGS -1 ; i++) { // Assuming MAX_ARGS is defined
  //    char arg_buf[10];
  //    sprintf(arg_buf, " arg%d", i);
  //    if (strlen(tc_max_args) + strlen(arg_buf) < MAX_BUFFER_SIZE -1)
  //        strcat(tc_max_args, arg_buf);
  //    else break;
  // }
  // parsed = parse_command(tc_max_args);
  // print_parsed_cmd_details(&parsed, "Command with many arguments");
  // free_parsed_command(&parsed);

  printf("All tests completed.\n");
  return 0;
}
