#include "shell.h"

/**
 * get_equal_sign - find the '=' character in a string
 *
 * @s: the string to search
 *
 * Return: the index where the character was found.
 * 0 is returned if the character was not found
 */
int get_equal_sign(const char *s)
{
	int i = 0;

	if (s[0] == '=')
		i = 1;
	for (; s[i]; i++)
		if (s[i] == '=')
			return (i);
	return (0);
}




/**
 * shellexit - exits the shell
 *
 * @self: the shell's state
 * @arguments: command line arguments passed to the shell
 *
 * Return: the exit value
 */
exit_status shellalias(state *self, char **arguments)
{
	int eq, i, status = 0;
	char *token;
	node *alias;

	if (!arguments[0])
	{
		print_list(self->aliases, true);
		return (0);
	}
	for (i = 0; arguments[i]; i++)
	{
		token = arguments[i];
		if (!token[0])
			break;
		eq = get_equal_sign(token);
		if (eq == 0)
		{
			alias = get_node(self->aliases, token);
			if (!alias)
			{
				fprinterr(format("alias: %s not found\n", token));
				status = 1;
			}
			else
				fprintout(format("%s='%s'\n",
					alias->var, alias->val));
		}
		else
		{
			token[eq] = '\0';
			set_node(&(self->aliases), token,
				remove_quotes(&token[eq + 1]));
		}
	}
	return (status);
}

/**
 * runalias - runs an alias
 *
 * @self: the shell's state
 * @command: the command to run
 * Return: true if it works or false if it fails
 */
bool runalias(state *self, char **command)
{

	int j;
	char **arguments, **tokens, *aliasi;
	bool status;
	size_t size, i;
	node *alias;

	tokens = &command[1];
	alias = get_node(self->aliases, command[0]);
	if (!alias)
		return (false);
	if (!alias->val || !*(alias->val))
		return (false);

	aliasi = _strdup(alias->val);
	self->buf = aliasi;
	arguments = split(aliasi, "\t ", 0, true);
	if (!arguments || !arguments[0])
		return (false);
	self->command = arguments;
	i = count_str(arguments);
	size = i + 1;
	for (j = 0; tokens[j] != NULL; j++)
	{
		appendStr(&arguments, &size, tokens[j], i);
		i++;
	}
	appendStr(&arguments, &size, NULL, i);
	status = runbuiltin(self, arguments);
	if (!status)
		status = runprogram(self, arguments);
	free(arguments);
	free(self->buf);
	self->command = NULL;
	self->buf = NULL;
	return (status);
}
