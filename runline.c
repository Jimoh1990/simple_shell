#include "shell.h"

/**
 * runcommand - run a single command
 *
 * @self: the shell's state
 * @command: the command name and arguments
 *
 * Return: nothing
 */
void runcommand(state *self, char **command)
{
	bool command_found;

	if (!command[0])
		return;
	command_found = runbuiltin(self, command);
	if (command_found == false)
		command_found = runprogram(self, command);
	if (command_found == false)
		command_found = runalias(self, command);
	if (command_found == false)
	{
		fprinterr(format("%s: %d: %s: not found\n",
			self->prog, self->lineno, command[0]));
		self->_errno = EKEYEXPIRED;
	}
}

/**
 * get_logical - get a logical operator from a line of commands
 *
 * @index: the index of the array to start searching from
 *
 * @next: an integer address where the next index after a logical
 * operator is inserted
 *
 * @tokens: a list of tokens found on a commandline
 *
 * Return:
 *		1 if logical and (&&) was found
 *		2 if logical or (||) was found
 *		0 if that is the last command
 */
int get_logical(char **tokens, int index, int *next)
{
	int i;

	for (i = index; tokens[i]; i++)
	{
		if (!_strcmp(tokens[i], "&&"))
		{
			tokens[i] = NULL;
			*next = i + 1;
			return (1);
		}
		if (!_strcmp(tokens[i], "||"))
		{
			tokens[i] = NULL;
			*next = i + 1;
			return (2);
		}
	}
	*next = index;
	return (0);
}

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
	char **tokens = split(line, "\t ", 0, true), **command;
	int index = 0, next, op, i;

	if (!tokens)
		return (0);
	self->tokens = tokens;
	for (i = 0; tokens[i]; i++)
		tokens[i] = replace(self, tokens[i]);
	command = tokens + index;
	op = get_logical(tokens, index, &next);
	if (!command[0] && op)
	{
		fprinterr(format("%s: %d: Syntax error: \"%s\" unexpected\n",
			self->prog, self->lineno, op == 1 ? "&&" : "||"));
		self->tokens = (free(self->tokens), NULL);
		self->_errno = 2;
		return (0);
	}
	runcommand(self, command);
	index = next;
	while (op)
	{
		if ((op == 2 && !self->_errno) ||
			(op == 1 && self->_errno))
		{
			op = get_logical(tokens, index, &next);
			index = next;
			continue;
		}
		command = tokens + index;
		op = get_logical(tokens, index, &next);
		runcommand(self, command);
		index = next;
	}
	free(self->tokens);
	self->tokens = NULL;
	return (0);
}
