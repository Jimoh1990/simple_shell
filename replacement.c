#include "shell.h"
/**
 * replace - replace a variable with something else
 *
 * @self: the variable to be replaced
 * @var: the value
 * Return: a string of the new variable
 */
char *replace(state *self, char *var)
{
	int len;
	node *n;
	size_t bufsize = 12;

	if (var[0] != '$')
		return (var);

	if (!_strcmp(var, "$$"))
	{
		return (self->pid_buf);
	}
	else if (!_strcmp(var, "$?"))
	{
		len = appendInt(&(self->errno_buf), &(bufsize), self->_errno, 0);
		appendChar(&(self->errno_buf), &(bufsize), '\0', len);
		return (self->errno_buf);
	}
	else if (var[0] && !var[1])
		return ("$");
	n = get_node(self->env, var + 1);
	if (!n)
		return ("");
	return (n->val);

}
