#include "shell.h"

/**
 * @brief Main function handling arguments and executing shell commands
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param env Environment variables
 * @return Exit code
 */
int main(int argc, char **argv, char **env) {
    char *command = NULL, **parsed_command = NULL;
    int path_count = 0, exit_code = 0, value = 0;
    (void)argc;

    while (1) {
        command = read_command(); // A function to read the command
        if (command) {
            path_count++;
            parsed_command = tokenize_command(command); // A function to tokenize the command
            if (!parsed_command) {
                free(command);
                continue;
            }
            if ((!compare_strings(parsed_command[0], "exit")) && parsed_command[1] == NULL)
                exit_command(parsed_command, command, exit_code); // A function to handle exit command
            if (!compare_strings(parsed_command[0], "env"))
                get_environment(env); // A function to retrieve environment variables
            else {
                value = path_values(&parsed_command[0], env); // A function to retrieve path values
                exit_code = fork_execution(parsed_command, argv, env, command, path_count, value); // Function to fork and execute command
                if (value == 0)
                    free(parsed_command[0]);
            }
            free(parsed_command);
        } else {
            if (is_interactive(STDIN_FILENO))
                write_output(STDOUT_FILENO, "\n", 1); // Function to write output
            exit(exit_code);
        }
        free(command);
    }
    return (exit_code);
}

