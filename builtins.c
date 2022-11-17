#include "shell.h"

/**
 * shellexit - exits the shell
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: the exit value
 */
exit_status shellexit(state *self, char **arguments)
{
	exit_status status = 0;
	char *arg = arguments[0];

	if (arg == NULL)
	{
		status = self->_errno;
		deinit(self);
		exit(status);
	}
	if (checkatoi(arg) == false)
	{
		fprinterr(format(
			"%s: %d: exit: Illegal number: %s\n",
			self->prog, self->lineno, arg
		));
		return (2);
	}
	else
		status = atoi(arg);
	deinit(self);
	exit(status);
}

/**
 * shellenv - prints out all shell environment variables
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: an integer representing the command's exit status
 */
exit_status shellenv(state *self, char **arguments)
{
	(void)arguments;
	print_list(self->env, false);
	return (0);
}

/**
 * shellsetenv - create/modify a shell enviroment variable
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: an integer representing the command's exit status
 */
exit_status shellsetenv(state *self, char **arguments)
{
	if (!arguments[0])
	{
		printerr("Usage: setenv VARIABLE VALUE\n");
		return (1);
	}
	else if (!arguments[1])
	{
		printerr("setenv: VALUE not supplied\n");
		return (2);
	}
	if (!set_node(&(self->env), arguments[0], arguments[1]))
	{
		perror("setenv");
		return (3);
	}
	return (0);
}

/**
 * shellunenv - delete a shell environment variable
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: an integer representing the command's exit status
 */
exit_status shellunsetenv(state *self, char **arguments)
{
	if (!arguments[0])
	{
		printerr("unsetenv: VARIABLE missing\n");
		return (1);
	}
	if (!get_node(self->env, arguments[0]))
	{
		fprinterr(format("unsetenv: %s does not exist\n", arguments[0]));
		return (2);
	}
	if (!delete_node(&(self->env), arguments[0]))
	{
		perror("unsetenv");
		return (3);
	}
	return (0);
}

/**
 * shellenv - change the shell's working directory
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: an integer representing the command's exit status
 */
exit_status shellcd(state *self, char **arguments)
{
	struct stat dir;
	char *cwd = getcwd(NULL, 0);
	char *path = arguments[0];
	node *pwd = set_default(&(self->env), "PWD", cwd);

	set_default(&(self->env), "OLDPWD", cwd);
	set_default(&(self->env), "HOME", "/root");
	free(cwd);
	cwd = NULL;

	if (!path || !_strcmp(path, "~"))
		path = get_node(self->env, "HOME")->val;
	else if (!_strcmp(path, "-"))
	{
		path = get_node(self->env, "OLDPWD")->val;
		printout(path),	printout("\n");
	}
	else if (path && path[0] == '-')
	{
		fprinterr(format("%s: %d: cd: Illegal option -",
			self->prog, self->lineno));
		write(STDIN_FILENO, path + 1, 1);
		printout("\n");
		return (2);
	}
	if (stat(path, &dir) == 0 && S_ISDIR(dir.st_mode)
		&& dir.st_mode & S_IXUSR)
	{
		cwd = (chdir(path), getcwd(NULL, 0));
		set_node(&(self->env), "OLDPWD", pwd->val);
		set_node(&(self->env), "PWD", cwd);
		free(cwd);
		return (0);
	}
	fprinterr(format(
		"%s: %d: cd: can't cd to %s\n",
		self->prog, self->lineno, path
	));
	return (2);
}
