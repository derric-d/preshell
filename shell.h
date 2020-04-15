#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LENGTH 1024
#define BLANK_STRING " "

int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strspn(char *s, char *accept);
void print_env(void);
void eof_routine(char *line);
char *read_line(void);
void free_dub(char **dub);
int exarg(char *input);
int get_tokens(char *line, const char *delimiters, char ***argvp);
void shell_loop(void);

#endif /* SHELL_H */
