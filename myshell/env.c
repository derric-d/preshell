#include "shell.h"

char *build_pathcmd(char *dest, char *src, char *cmd, int n, int c)
{

	int i, j;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '/';
	i++;
	j = 0;

	for (j = 0; j < c && cmd[j] != '\0'; j++, i++)
	{
		dest[i] = cmd[j];
	}
	dest[i] = '\0';
	return (dest);
}
char **env_array(char *cmd, char **environ)
{
	char **env_dirs;
	char *path, *dir;
	unsigned int path_count, i;
	int  dir_len, cmd_len;

	path = _getenv("PATH", environ);
	path_count = count_path_dir(path);
	env_dirs = malloc(sizeof(char *) * (path_count + 1));

	if (!env_dirs)
		return (NULL);

	i = 0;
	dir = strtok(path, ":");
	while (dir)
	{
		dir_len = strlen(dir);
		cmd_len = strlen(cmd);

		env_dirs[i] = malloc(sizeof(char) * (dir_len + cmd_len + 2));
		if (!env_dirs[i])
		{
			free_dub(env_dirs);
			return (NULL);
		}
		build_pathcmd(env_dirs[i], dir, cmd, dir_len, cmd_len);
		i++;
		dir = strtok(NULL, ":");
	}
	env_dirs[i] = NULL;
	return (env_dirs);
}
char *_getenv(char *name, char **environ)
{
	char *env_var, *name_cpy;
	unsigned int i = 0, len;

	len = strlen(name);
	name_cpy = malloc((sizeof(char) * len) + 1);
	if (!name_cpy)
		return (NULL);

	strncpy(name_cpy, name, len);
	env_var = strtok(environ[i], "=");

	while (environ[i])
	{
		if (strcmp(env_var, name_cpy) == 0)
		{
			env_var = strtok(NULL, "\n");
			free(name_cpy);
			name_cpy = NULL;
			return (env_var);
		}
		i++;
		env_var = strtok(environ[i], "=");
	}
	free(name_cpy);
	name_cpy = NULL;
	return (NULL);
}
void _printenv(char **env)
{
	unsigned int i, len;

	while (env[i])
	{
		len = strlen(env[i]);
		write(1, env[i], len);
		write(1, "\n", 1);
		i++;
	}
}
void exec_env(char *line, char **chargv, char **env)
{
	free(line);
	line = NULL;
	free(chargv);
	chargv = NULL;
	_printenv(env);
	exit(EXIT_SUCCESS);
}

