#include "shell.h"

/**
 * findquote - finds an unescaped quote in a string
 * @str: the string to search
 * @quote: the quote to search for (could be " or ')
 * Return: the index where the unescaped quote was found, or -1
 *		if the quote wasn't found.
 */
int findquote(char *str, char quote)
{
	char next, curr, c;
	int i;

	if (str == NULL || *str == '\0')
		return (-1);

	if (quote == '"')
		c = '"';
	else
		c = '\'';

	for (i = 0; str[i] != '\0'; i++)
	{
		curr = str[i];
		next = str[i + 1];

		if (curr == c)
			return (i);
		if (next == c && curr != '\\')
			return (i + 1);
		else if (next)
			i++;
	}
	return (-1);
}
/**
 * comment - Identifies a comment in command line
 *
 * @av: the command line arguments
 * Return: Nothing. It is void
 */
void comment(char *av[])
{
	int j;

	if (av == NULL)
		return;
	for (j = 0; av[j]; j++)
	{
		if (_strcmp(av[j], "#") == 0)
		{
			av[j] = NULL;
			break;
		}
	}
}
