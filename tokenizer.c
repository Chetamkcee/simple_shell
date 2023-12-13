#include "shell.h"

/**
 * allocate_tokens - Allocates memory for an array of strings.
 * @token_count: Number of tokens.
 * @copy: Copy of the command line.
 *
 * Return: Pointer to the array of strings.
 */
char **allocate_tokens(size_t token_count, char *copy)
{
	char **user_command = malloc((token_count + 1) * sizeof(char *));

	if (user_command == NULL)
	{
		free(copy);
		return (NULL);
	}
	return (user_command);
}

/**
 * count_tokens - Counts the number of tokens in a string.
 * @copy: Copy of the command line.
 *
 * Return: Number of tokens.
 */
size_t count_tokens(char *copy)
{
	size_t token_count = 0;

	char *token = _strtok(copy, " \n\t\r");

	while (token != NULL)
	{
		token_count++;
		token = _strtok(NULL, " \n\t\r");
	}
	return (token_count);
}

/**
 * get_tokens - Splits a string into tokens.
 * @command_line: Command line.
 *
 * Return: Pointer to the array of strings.
 */
char **get_tokens(char *command_line)
{
	char *copy, **user_command, *token;

	size_t token_count = 0, j = 0, i = 0;

	if (command_line == NULL)
		return (NULL);

	copy = strdup(command_line);

	if (copy == NULL)
		return (NULL);

	token_count = count_tokens(copy);

	user_command = allocate_tokens(token_count, copy);

	if (user_command == NULL)
	{
		free(copy);
		return (NULL);
	}

	token = _strtok(copy, " \n\t\r");

	while (token != NULL && i < token_count)
	{
		user_command[i] = strdup(token);
		if (user_command[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(user_command[j]);
			free(user_command);
			free(copy);
			return (NULL);
		}
		token = _strtok(NULL, " \n\t\r");
		i++;
	}
	user_command[i] = NULL;

	free(copy);
	return (user_command);
}
