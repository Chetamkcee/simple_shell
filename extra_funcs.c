#include shell.h

/** 
 * getline - function that returns the a line passed to the interpreter
 *
 * return: a pointer to the buffer
 */

char *read_command(void)
{
        size_t n = 0;
        char *lineptr = NULL;
        char *line = NULL;

        if (isatty(stdin))
                write(STDOUT_FILENO, "$ ", 2);

        line = getline(&lineptr, &n, stdin);
        if (!line)
        {
                free(lineptr);
                return(NULL);
        }
        return lineptr;
}

/**
 * handle_exit_command - Function to handle the exit command in the shell
 * @arguments Command arguments
 * @input String from standard input
 * @exit_code Exit code value
 * return None
 */
void handle_exit_command(char **arguments, char *input, int exit_code) {
    int status = 0;

    if (!arguments[1]) {
        free(input);
        free(arguments);
        exit(exit_code);
    }
    status = convert_to_integer(arguments[1]);

    free(input);
    free(arguments);
    exit(status);
}

/**
 * display_environment - Function to retrieve and display environment variables
 * @environment Environment variables
 * @return None
 */
void display_environment(char **environment) {
    size_t index = 0;

    while (environment[index]) {
        write_output(STDOUT_FILENO, environment[index], string_length(environment[index]));
        write_output(STDOUT_FILENO, "\n", 1);
        index++;
    }
}