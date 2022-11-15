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
	int i;

	for (i = 0; s[i]; i++)
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
	int eq, i, status;
	char *token;
	node *alias;

	status = 0;

	if (!arguments[0])
	{
		print_list(self->aliases);
		return (0);
	}
	for (i = 0; arguments[i]; i++)
	{
		token = arguments[i];
		eq = get_equal_sign(token);
		if (!eq)
		{
			alias = get_node(self->aliases, token);
			if (!alias)
			{
				fprinterr(format("alias: %s not found\n", token));
				status = 1;
			}
			else
			{
				fprintout(format("%s=%s\n",
					alias->var, (!alias->val[0]) ? "''" : alias->val));
			}
		}
		else
		{
			token[eq] = '\0';
			set_node(&(self->aliases), token, &token[eq + 1]);
		}
	}
	return (status);
}
