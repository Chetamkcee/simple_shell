#include shell.h

/** 
* getline - function that returns the a line passed to the interpreter
 *
 * return: a pointer to the buffer
 */

char * getline(void)
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
