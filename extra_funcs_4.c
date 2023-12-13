#include "shell.h"

/**
 * separate_path_values - Separate the path into new strings.
 * @arg: User input command.
 * @env: Environment variables.
 * Return: Integer indicating success or failure.
 */
int separate_path_values(char **arg, char **env) {
    char *token = NULL, *path_relative = NULL, *path_absolute = NULL;
    size_t path_length, command_length;
    struct stat stat_info;

    if (stat(*arg, &stat_info) == 0)
        return (-1);

    path_relative = get_path_value(env);
    if (!path_relative)
        return (-1);

    token = _strtok(path_relative, ":");
    command_length = string_length(*arg);

    while (token) {
        path_length = string_length(token);
        path_absolute = (char *)malloc(sizeof(char) * (path_length + command_length + 2));

        if (!path_absolute) {
            free(path_relative);
            return (-1);
        }

        path_absolute = string_copy(path_absolute, token);
        string_concatenate(path_absolute, "/");
        string_concatenate(path_absolute, *arg);

        if (stat(path_absolute, &stat_info) == 0) {
            *arg = path_absolute;
            free(path_relative);
            return (0);
        }

        free(path_absolute);
        token = _strtok(NULL, ":");
    }

    free(path_relative);
    return (-1);
}

/**
 * get_path_value - Get the value of the PATH variable.
 * @env: Local environment
 * Return: Value of the PATH variable
 */
char *get_path_value(char **env) {
    size_t index = 0, var = 0, count = 5;
    char *path = NULL;

    for (index = 0; string_compare_n(env[index], "PATH=", 5); index++)
        ;

    if (env[index] == NULL)
        return (NULL);

    for (count = 5; env[index][var]; var++, count++)
        ;

    path = (char *)malloc(sizeof(char) * (count + 1));

    if (path == NULL)
        return (NULL);

    for (var = 5, count = 0; env[index][var]; var++, count++)
        path[count] = env[index][var];

    path[count] = '\0';
    return (path);
}

/**
 * execute_fork - Function that creates a fork for command execution
 * @arg: Command and path values
 * @av: Name of the program
 * @env: Environment variables
 * @lineptr: User's command line
 * @process_id: Process ID
 * @checker: Checker flag for additional test
 * Return: 0 on success
 */
int execute_fork(char **arg, char **av, char **env, char *lineptr, int process_id, int checker) {
    pid_t child;
    int status = 0;
    char *error_format = "%s: %d: %s: not found\n";

    child = fork();

    if (child == 0) {
        if (execve(arg[0], arg, env) == -1) {
            fprintf(stderr, error_format, av[0], process_id, arg[0]);
            if (!checker)
                free(arg[0]);
            free(arg);
            free(lineptr);
            exit(errno);
        }
    } else {
        wait(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return (WEXITSTATUS(status));
    }
    return (0);
}