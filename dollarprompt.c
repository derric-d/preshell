#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_LENGTH 1024
#define BLANK_STRING " "
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

	//printf("you entered: %s \n", line);
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

//	get_tokens(input, BLANK_STRING, &chargv);
/*
	if (args[0] == NULL)
		return (1);
*/
	if (pid == 0)
	{
	/*
		res_get_t = get_tokens(input, BLANK_STRING, &chargv);
		if (res_get_t <= 0)
		{
			perror("parse error\n");
			return(1);
		}*/
		get_tokens(input, BLANK_STRING, &chargv);
		for (y = 0; chargv[y]; y++)
			printf("%s\n", chargv[y]);
		exec_res = execvp(chargv[0], chargv);
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
	
	while (*((*argvp) + cnt))
	{
		printf("%s\n", *((*argvp) + cnt));
		cnt++;
	}
	printf("numtokens : %d\n", numtokens);
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
		//get_tokens(line, BLANK_STRING, &args);
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
/*
void executecmd(char *incmd)
{
  char **chargv;
    if (get_tokens(incmd, BLANK_STRING, &chargv) <= 0)
    {
        fprintf(stderr, "Failed to parse command line\n");
        exit(1);
    }
    printf("%s", chargv[0]);
    execvp(chargv[0], chargv);
    perror("Failed to execute command");
    exit(1);
}

*/
/*exarg alternative*/
/*	pid_t pid, wpid;
	int i = 0, status, exec_res;

	pid = fork();

	if (args[0] == NULL)
		return (1);

	if (pid == 0)
	{
		exec_res = execve(args[0], args, NULL);
		if (exec_res== -1)
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
	*/
/* get_tokens alternative*/
#if 0
	char **token_list;
	char *token, *s;
	unsigned int commands = 0;
	int i = 0, j = 0, isword;

	line[strlen(line) - 1] = '\0';

	s = line;
	while(s[i] != '\0')
	{
		if (s[i] != ' ')
			isword = 1;

		if ((isword && s[i + 1] == ' ') || (isword && s[i + 1] == '\0'))
		{
			commands++;
			isword = 0;
		}
		i++;
	}
	if (commands == 0)
		return (NULL);
	
	token_list = malloc(sizeof(char *) * (commands + 1));
	if (!token_list)
		return (NULL);
	token = strtok(line, " ");
	while (token)
	{
		token_list[j] = malloc(strlen(token) + 1);
		if (!token_list[j])
		{
			free_dub(token_list);
			return (NULL);
		}
		strncpy(token_list[j], token, strlen(token) + 1);
		token = strtok(NULL, " ");
		++i;
	}

	return (token_list);
	#endif

