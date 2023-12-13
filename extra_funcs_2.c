#include "shell.h"

/**
 * myStrspn - Gets the length of a prefix substring.
 * @str1: String to be scanned.
 * @str2: String containing the characters to match.
 * Return: The number of characters in the initial segment of str1 which
 * consist only of characters from str2.
 */
size_t myStrspn(const char *str1, const char *str2)
{
	size_t i, j;
	i = 0;

	while (*(str1 + i))
	{
		j = 0;
		while (*(str2 + j))
		{
			if (*(str1 + i) == *(str2 + j))
			{
				break; // Found a match.
			}
			j++;
		}
		if (!*(str2 + j))
		{
			return i; // No match found.
		}
		i++;
	}
	return i;
}
/**
 * _strchr - locates the ﬁrst occurrence of c (converted to a char) in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string.
 * @s: string
 * @c: character
 * Return: a pointer to the located character, or a null pointer
 * if the character does not occur in the string.
 **/
char *_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (0);
	return ((char *)s);
}

/**
 * _strcspn - Finds the length of the segment in 's1'
 * that does not contain any characters from 's2'.
 * @s1 The string to check
 * @s2 The string used for comparison
 * return The length of the segment
 */
size_t _strcspn(const char *s1, const char *s2)
{
	size_t ret = 0;

	while (*s1)
	{
		if (_strchr(s2, *s1))
			return ret;
		s1++;
		ret++;
	}
	return ret;
}

/**
 * _strtok - Tokenizes a string based on the given delimiter.
 * @str The string to tokenize
 * @delim The delimiter string
 * return The first/next token if possible, NULL otherwise
 */
char *_strtok(char *str, const char *delim)
{
	static char *p;

	if (str)
	{
		p = str;
	}
	else if (!p)
	{
		return NULL;
	}

	str = p + myStrspn(p, delim);
	p = str + _strcspn(str, delim);

	if (p == str)
	{
		p = NULL;
		return NULL;
	}

	if (*p != '\0')
	{
		*p = '\0';
		p++;
	}
	else
	{
		p = NULL;
	}

	return str;
}

/**
 * get_tokens - Get tokens from a string
 * @command_line: User command
 * Return: Pointer to tokens
 */

char **get_tokens(char *command_line)
{
	if (command_line == NULL)
		return NULL;

	// Count the number of tokens
	size_t token_count = 0;
	char *copy = strdup(command_line);
	if (copy == NULL)
		return NULL;

	char *token = _strtok(copy, " \n\t\r");
	while (token != NULL)
	{
		token_count++;
		token = _strtok(NULL, " \n\t\r");
	}

	// Allocate memory for an array of pointers
	char **user_command = malloc((token_count + 1) * sizeof(char *));
	if (user_command == NULL)
	{
		free(copy);
		return NULL;
	}

	// Reset command_line and token
	token = _strtok(copy, " \n\t\r");

	size_t i = 0;
	while (token != NULL && i < token_count)
	{
		user_command[i] = strdup(token); // Allocate memory for each token
		if (user_command[i] == NULL)
		{
			// Handle memory allocation failure
			for (size_t j = 0; j < i; j++)
			{
				free(user_command[j]);
			}
			free(user_command);
			free(copy);
			return NULL;
		}
		token = _strtok(NULL, " \n\t\r");
		i++;
	}
	user_command[i] = NULL;

	free(copy); // Free the copied command_line string
	return user_command;
}
