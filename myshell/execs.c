#include "shell.h"

int exarg(char *input, char **env)
{
	pid_t pid;
	int status, exec_res;
	struct stat filestat;
	char **chargv;

	pid = fork();
	if (pid == 0)
	{
		get_tokens(input, BLANK_STRING, &chargv);
		if (chargv == NULL)
		{
			free(input);
			input = NULL;
			exit(EXIT_SUCCESS);
		}
		else if (strcmp("env", chargv[0]) == 0)
			exec_env(input, chargv, env);
		else if (stat(chargv[0], &filestat) == 0)
		{
			exec_res = execve(chargv[0], chargv, NULL);
			if (exec_res < 0)
				perror("exec error");
			exit(EXIT_FAILURE);
		}
		else
		{
			exec_path(chargv, input, env);
		}
	}
	else if (pid < 0)
	{
		perror("forking err");
	}
	else
	{
		do {
			wait(&status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
void exec_path(char **chargv, char *input, char **env)
{
	struct stat pathstat;
	int i = 0;
	char **pathdirs;

	pathdirs = env_array(chargv[0], env);
	while (pathdirs[i])
	{
		if (stat(pathdirs[i], &pathstat) == 0)
			execve(pathdirs[i], chargv, NULL);
		i++;
	}
	/* if no command found, ERROR  */

	free(input);
	input = NULL;
	free_dub(chargv);
	free_dub(pathdirs);
	exit(EXIT_SUCCESS);
}

void eof_routine(char *line)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(line);
	line = NULL;
	exit(0);
}

