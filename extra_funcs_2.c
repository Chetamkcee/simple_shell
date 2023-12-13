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
