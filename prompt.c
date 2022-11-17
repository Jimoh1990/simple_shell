#include "shell.h"

/**
 * print_pwd - print the process' working directory in style ✨
 *
 * @self: the shell's state
 *
 * Return: nothing
 */
void print_pwd(state *self)
{
	char *home, *pwd;
	int lenhome, lenpwd, i;
	bool isrel;

	home = set_default(&(self->env), "HOME", "/root")->val;
	pwd = getcwd(NULL, 0);
	lenhome = _strlen(home);
	lenpwd = _strlen(pwd);
	isrel = true;

	if (!_strcmp(pwd, "/"))
		printout("/");
	else
	{
		for (i = 0; i < lenhome; i++)
			if (home[i] != pwd[i])
			{
				isrel = false;
				break;
			}
		if (isrel == false)
			for (i = 0; i < lenpwd; i++)
			{
				if (!ispath(&pwd[i]))
				{
					printout(&pwd[i]);
					break;
				}
			}
		else
		{
			printout("~");
			for (i = lenhome; i < lenpwd; i++)
				write(STDIN_FILENO, &pwd[i], 1);
		}
	}
	free(pwd);
}

/**
 * prompt - print out the prompt for interactive mode
 *
 * @self: the shell's state
 *
 * Return: nothing
 */
void prompt(state *self)
{
	if (self->_errno)
		printout("\033[0;31m");
	else
		printout("\033[0;34m");
	printout("➜");
	printout("\033[0m");
	printout(" ");
	printout("\033[0;32m");
	printout("[");
	printout("\033[0m");
	print_pwd(self);
	printout("\033[0;32m");
	printout("]");
	printout("\033[0m");
	printout(" $ ");
}
