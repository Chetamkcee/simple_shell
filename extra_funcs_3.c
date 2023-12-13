#include "shell.h"
#include <stddef.h>

/**
 * string_concatenate - Concatenates src string to the end of dest string.
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *string_concatenate(char *dest, char *src)
{
    int dest_index = 0;
    int src_index = 0;

    while (dest[dest_index] != '\0')
    {
        dest_index++;
    }
    while (src[src_index] != '\0')
    {
        dest[dest_index] = src[src_index];
        dest_index++;
        src_index++;
    }
    dest[dest_index] = '\0';
    return dest;
}

/**
 * string_compare - Compares two strings.
 * @s1: First string
 * @s2: Second string
 * Return: Integer indicating the comparison result
 */
int string_compare(char *s1, char *s2)
{
    int index;

    for (index = 0; s1[index] != '\0' && s2[index] != '\0'; index++)
    {
        if (s1[index] != s2[index])
        {
            return ((int)s1[index] - s2[index]);
        }
    }
    return 0;
}

/**
 * string_length - Calculates the length of a string.
 * @s: Pointer to the string
 * Return: Length of the string
 */
int string_length(char *s)
{
    int length = 0;

    while (*(s + length) != '\0')
    {
        length++;
    }

    return length;
}

/**
 * string_compare_n - Compares the first n characters of two strings.
 * @s1: First string
 * @s2: Second string
 * @n: Number of characters to compare
 * Return: Difference between the strings
 */
size_t string_compare_n(char *s1, char *s2, size_t n)
{
    size_t index, diff;

    for (index = 0; s1[index] != '\0' && index < n; index++)
    {
        diff = s1[index] - s2[index];

        if (diff != 0)
        {
            return diff;
        }
    }
    return 0;
}

/**
 * string_copy - Copies the source string to the destination string.
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *string_copy(char *dest, char *src)
{
    int i = 0;

    while (*(src + i) != '\0')
    {
        *(dest + i) = *(src + i);
        ++i;
    }
    *(dest + i) = *(src + i);

    return dest;
}

