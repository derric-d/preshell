#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_LENGTH 1024
#define BLANK_STRING " "

int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
unsigned int _strspn(char *s, char *accept);

#endif /* SHELL_H */
