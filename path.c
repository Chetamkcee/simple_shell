#include "shell.h"

/**
 * create_absolute_path - creates an absolute path from a relative path
 * @path: the relative path
 * @command: the command to concatenate to the path
 *
 * Return: the absolute path
 */
char *create_absolute_path(char *path, char *command)
{
	size_t path_length = string_length(path);
	size_t command_length = string_length(command);
	char *path_absolute = (char *)malloc(sizeof(char) *
										 (path_length + command_length + 2));

	if (!path_absolute)
		return (NULL);

	path_absolute = string_copy(path_absolute, path);
	string_concatenate(path_absolute, "/");
	string_concatenate(path_absolute, command);

	return (path_absolute);
}

/**
 * check_path - checks if the path is valid
 * @arg: the argument to check
 * @path_absolute: the absolute path
 * @stat_info: the stat struct
 *
 * Return: 0 on success, -1 on failure
 */
int check_path(char **arg, char *path_absolute, struct stat stat_info)
{
	if (stat(path_absolute, &stat_info) == 0)
	{
		*arg = path_absolute;
		return (0);
	}
	free(path_absolute);
	return (-1);
}

/**
 * separate_path_values - separates the path values
 * @arg: the argument to check
 * @env: the environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int separate_path_values(char **arg, char **env)
{
	char *token = NULL, *path_relative = NULL, *path_absolute = NULL;
	struct stat stat_info;

	if (stat(*arg, &stat_info) == 0)
		return (-1);

	path_relative = get_path_value(env);
	if (!path_relative)
		return (-1);

	token = _strtok(path_relative, ":");

	while (token)
	{
		path_absolute = create_absolute_path(token, *arg);

		if (!path_absolute)
		{
			free(path_relative);
			return (-1);
		}

		if (check_path(arg, path_absolute, stat_info) == 0)
		{
			free(path_relative);
			return (0);
		}
		token = _strtok(NULL, ":");
	}
	free(path_relative);
	return (-1);
}
