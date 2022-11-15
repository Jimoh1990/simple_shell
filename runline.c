#include "shell.h"

/**
 * runline - run a single line of command
 *
 * @self: the shell's state
 * @line: line to run
 *
 * Return: alway 0
 */
int runline(state *self, char *line)
{
	bool command_found;
	int i;
	char **tokens;

	tokens = split(line, "\t ", 0);
	if (!tokens)
		return (0);
	self->tokens = tokens;
	for (i = 0; tokens[i]; i++)
	{
		tokens[i] = replace(self, tokens[i]);
	}
	comment(tokens);
	command_found = runbuiltin(self, tokens);
	if (command_found == false)
		command_found = runprogram(self, tokens);
	if (command_found == false)
	{
		fprinterr(format("%s: %d: %s: not found\n",
			self->prog, self->lineno, tokens[0]));
		self->_errno = EKEYEXPIRED;
	}
	free(self->tokens);
	self->tokens = NULL;
	return (0);
}
