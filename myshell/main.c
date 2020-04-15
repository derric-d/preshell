#include "shell_2.h"


/**
 * exec_sig - executes on signal interupt
 *
 * @sig: signal value passed
 */
void exec_sig(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$", 3);
}
/**
 * read_line - gets the command line input
 *
 * Return: returns the command line input
 */
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
/**
 * main - entry point
 * @ac: argument count
  * @av: argument vector
  * @env: environment list
 * Return: = on success
 */
int main(int ac, char **av, char **env)
{
	char *line;
	int status = 1;
	(void)ac;
	(void)av;
	signal(SIGINT, exec_sig);
	do {
		printf("$ ");
		line = read_line();
		if (strcmp(line, "exit\n") == 0)
		{
			return status;
		}
		status = exarg(line, env);
		free(line);
	} while (1);
	return (0);
}

