#include "shell.h"
/**
 * main - Main function handling arguments and executing shell commands
 * @argc Number of arguments
 * @argv Array of arguments
 * @env Environment variables
 * return Exit code
 */
int main(int argc, char **argv, char **env) {
    char *command = NULL, **parsed_command = NULL;
    int path_count = 0, exit_code = 0, value = 0;
    (void)argc;

    while (1) {
        command = read_command();
        if (command) {
            path_count++;
            parsed_command = get_tokens(command);
            if (!parsed_command) {
                free(command);
                continue;
            }
            if ((!string_compare(parsed_command[0], "exit")) && parsed_command[1] == NULL)
                exit_command(parsed_command, command, exit_code);
            if (!string_compare(parsed_command[0], "env"))
                display_environment(env);
            else {
                value = separate_path_values(&parsed_command[0], env);
                exit_code = execute_fork(parsed_command, argv, env, command, path_count, value);
                if (value == 0)
                    free(parsed_command[0]);
            }
            free(parsed_command);
        } else {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            exit(exit_code);
        }
        free(command);
    }
    return (exit_code);
}