#include "shell.h"

void exec_sig(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$", 3);
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
		exarg(line, env);
		free(line);
	} while (status);
	return (0);
}

