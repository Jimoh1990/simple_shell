#include "shell.h"

/**
 * ispath - check if a string is a path
 *
 * @s: the string to check
 *
 * Return: true(1) if the string is a path, else false(0)
 */
bool ispath(const char *s)
{
	int i;

	if (!s)
		return (false);
	for (i = 0; s[i]; i++)
		if (s[i] == '/')
			return (true);
	return (false);
}

/**
 * joinpath - join two paths together using /
 *
 * @base: the base path
 * @child: the child path
 *
 * Return: A new malloced string where base and child are stringed
 * together like this: base/child
 *
 * NOTE: if one of the strings is NULL, it returns NULL
 */
char *joinpath(const char *base, const char *child)
{
	char *newpath;
	int baselen, childlen, i, index;
	bool has_sep;

	baselen = childlen = index = 0;
	has_sep = false;

	if (!(base && child))
		return (NULL);

	baselen = _strlen(base);
	childlen = _strlen(child);

	if (base[baselen - 1] == '/' || child[0] == '/')
		has_sep = true;

	newpath = malloc(
		/* create space for a nullbyte and space for the / */
		baselen + childlen + 2
	);

	for (i = 0; i < baselen; i++)
		newpath[index++] = base[i];
	if (!has_sep)
		newpath[index++] = '/';
	for (i = 0; i < childlen; i++)
		newpath[index++] = child[i];
	newpath[index] = '\0';
	return (newpath);
}
