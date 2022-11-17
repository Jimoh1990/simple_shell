#include "shell.h"

/**
 * findfile - searches through a directory for a file
 *
 * @dir: the directory to search
 * @filename: name of the file to search for
 *
 * Return: a pointer to the file if found, else NULL
 */
struct dirent *findfile(DIR *dir, const char *filename)
{
	struct dirent *file;

	errno = 0;
	file = readdir(dir);
	while (file != NULL)
	{
		if (_strcmp(filename, file->d_name) == 0)
			break;
		file = readdir(dir);
	}
	return (file);
}


/**
 * findcmd - searches through $PATH to find a command
 *
 * @command: name of the command
 * @PATH: a string containing directories in which to search
 * for the command. The directories should be delimited by :
 *
 * Return: a pointer to the path of the command if found, otherwise NULL
 */
char *findcmd(const char *command, const char *PATH)
{
	char **dirs, *dirname, *PATHCPY, *cmd;
	DIR *dir;
	struct dirent *node;
	int i;

	cmd = NULL;
	PATHCPY = _strdup(PATH);
	dirs = split(PATHCPY, ":", 0, false);
	if (!dirs)
		return (NULL);

	for (i = 0; dirs[i]; i++)
	{
		dirname = dirs[i];
		dir = opendir(dirname);
		if (!dir)
			continue;
		node = findfile(dir, command);
		if (node)
		{
			cmd = joinpath(dirname, node->d_name);
			closedir(dir);
			break;
		}
		closedir(dir);
	}
	free(PATHCPY);
	free(dirs);
	return (cmd);
}
