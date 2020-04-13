#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_LENGTH 1024
#define BLANK_STRING " "

void print_env(void)
{

	extern char **environ;
	int i;

	if (!environ)
		return;
	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}
void eof_routine(char *line)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(line);
	exit(0);
}

char *read_line(void)
{
	char *line = NULL;
	size_t linesize = MAX_LENGTH;
	int get_line_res;

	get_line_res = getline(&line, &linesize, stdin);
	if (get_line_res == EOF)
		eof_routine(line);

	return (line);
}
void free_dub(char **dub)
{
	unsigned int i = 0;
	if (!dub)
		return;
	while(dub[i])
	{
		free(dub);
		i++;
	}
	if (dub[i] == NULL)
		free(dub[i]);
	free(dub);
}
int exarg(char *input)
{
	pid_t pid, wpid;
	int i = 0, status, exec_res, res_get_t, y;
	char **chargv;

	pid = fork();
	if (pid == 0)
	{
		get_tokens(input, BLANK_STRING, &chargv);
		exec_res = execve(chargv[0], chargv, NULL);
		if (exec_res < 0)
			perror("exec err");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("forking err");
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
int get_tokens(char *line, const char *delimiters, char ***argvp)
{
	int error, i, numtokens = 0, cnt = 0;
	char *t;
	const char *snew;
	line[strlen(line) - 1] = '\0';
	if ((line == NULL) || (delimiters == NULL) || (argvp == NULL))
	{
		errno = EINVAL;
		return (-1);
	}
	*argvp = NULL;
	snew = line + strspn(line, delimiters);
	if ((t = malloc(strlen(snew) + 1)) == NULL)
		return (-1);
	strcpy(t, snew);
	if (strtok(t, delimiters) != NULL)
		for (numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++)
			;

	if ((*argvp = malloc((numtokens + 1) * sizeof(char *))) == NULL)
	{
		error = errno;
		free(t);
		errno = error;
		return (-1);
	}
	if (numtokens == 0)
		free(t);
	else
	{
		strcpy(t, snew);
		**argvp = strtok(t, delimiters);
		for (i = 1; i < numtokens; i++)
			*((*argvp) + i) = strtok(NULL, delimiters);
	}
	*((argvp) + numtokens) = NULL;

	return (numtokens);
}
void shell_loop(void)
{
	char *line;
	char **args;
	int status = 1;

	do {
		printf("$ ");
		line = read_line();
		if (strcmp(line, "exit\n") == 0)
			break;
		if (strcmp(line, "env\n") == 0)
			print_env();
		else
			exarg(line);

		free(line);
		free(args);
	} while (status);
}
int main(int ac, char **av)
{
	shell_loop();

	return (0);
}
