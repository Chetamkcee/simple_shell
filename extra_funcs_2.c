#include shell.h
#include <stddef.h>

/**
 * _strcspn - Finds the length of the segment in 's1' that does not contain any characters from 's2'.
 * @s1 The string to check
 * @s2 The string used for comparison
 * return The length of the segment
 */
size_t _strcspn(const char *s1, const char *s2) {
    size_t ret = 0;

    while (*s1) {
        if (custom_strchr(s2, *s1))
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
char *_strtok(char *str, const char *delim) {
    static char *p;

    if (str) {
        p = str;
    } else if (!p) {
        return NULL;
    }

    str = p + _strspn(p, delim);
    p = str + _strcspn(str, delim);
    
    if (p == str) {
        p = NULL;
        return NULL;
    }

    if (*p != '\0') {
        *p = '\0';
        p++;
    } else {
        p = NULL;
    }

    return str;
}

/**
 * get_tokens - Get tokens from a string
 * @command_line: User command
 * Return: Pointer to tokens
 */
char **get_tokens(char *command_line) {
    char **user_command = NULL;
    char *token = NULL;
    size_t i = 0;
    int size = 0;

    if (command_line == NULL)
        return NULL;

    for (i = 0; command_line[i]; i++) {
        if (command_line[i] == ' ')
            size++;
    }
    if ((size + 1) == string_length(command_line))
        return NULL;

    user_command = malloc(size + 2, sizeof(char *));
    if (user_command == NULL)
        return NULL;

    token = _strtok(command_line, " \n\t\r");
    for (i = 0; token != NULL; i++) {
        user_command[i] = token;
        token = _strtok(NULL, " \n\t\r");
    }
    user_command[i] = NULL;
    return user_command;
}