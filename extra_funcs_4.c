#include "shell.h"
/**
 * get_path_value - Get the value of the PATH variable.
 * @env: Local environment
 * Return: Value of the PATH variable
 */
char *get_path_value(char **env)
{
	size_t index = 0, var = 0, count = 5;
	char *path = NULL;

	for (index = 0; env[index] != NULL &&
					string_compare_n(env[index], "PATH=", 5);
		 index++)
		;

	if (env[index] == NULL)
		return (NULL);

	for (count = 5; env[index][var] != '\0'; var++, count++)
		;

	path = (char *)malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[index][var] != '\0'; var++, count++)
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
int execute_fork(char **arg, char **av, char **env,
				 char *lineptr, int process_id, int checker)
{
	pid_t child;
	int status = 0;
	char *error_format = "%s: %d: %s: not found\n";

	child = fork();

	if (child == 0)
	{
		if (execve(arg[0], arg, env) == -1)
		{
			fprintf(stderr, error_format, av[0], process_id, arg[0]);
			if (!checker)
				free(arg[0]);
			free(arg);
			free(lineptr);
			exit(errno);
		}
	}
	else
	{
		wait(&status);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
	}
	return (0);
}
