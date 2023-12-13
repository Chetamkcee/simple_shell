#ifndef _SHELL_H_
#define _SHELL_H_
#define _GNU_SOURCE

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *read_command(void);
void exit_command(char **arguments, char *input, int exit_code);
void display_environment(char **environment);
size_t _strcspn(const char *s1, const char *s2);
char *_strtok(char *str, const char *delim);
char *string_concatenate(char *dest, char *src);
int string_compare(char *s1, char *s2);
int string_length(char *s);
size_t string_compare_n(char *s1, char *s2, size_t n);
char *string_copy(char *dest, char *src);
int separate_path_values(char **arg, char **env);
char *get_path_value(char **env);
int execute_fork(char **arg, char **av, char **env, char *lineptr, int process_id, int checker);
#endif