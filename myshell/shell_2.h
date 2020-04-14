#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_LENGTH 1024
#define BLANK_STRING " "

void free_dub(char **dub);
int get_tokens(char *line, const char *delimiters, char ***argvp);
unsigned int count_path_dir(char *path);
char *build_pathcmd(char *dest, char *src, char *cmd, int n, int c);
char **env_array(char *cmd, char **environ);
char *_getenv(char *name, char **environ);
void _printenv(char **env);
void exec_env(char *line, char **chargv, char **env);
int exarg(char *input, char **env);
void exec_path(char **chargv, char *input, char **env);
void eof_routine(char *line);
char *read_line(void);

#endif