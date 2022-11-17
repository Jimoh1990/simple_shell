#include "shell.h"
#include "strings.h"

/**
 * _strdup - duplicate a string
 *
 * @str: string to duplicate
 *
 * Return: new string or NULL if malloc failed
 */
char *_strdup(const char *str)
{
	char *s;
	unsigned int i, l;

	if (str == NULL)
		return (NULL);
	l = _strlen(str);
	s = malloc(l + 1);
	if (!s)
		return (NULL);
	for (i = 0; i < l; i++)
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}


/**
 * _strlen - it swaps the values of two integers
 * Description:'A function'
 * @s: the string to be checked
 * Return: The lenght of the string
 */
int _strlen(const char *s)
{
	int i, lenght;

	if (s == NULL)
		return (-1);

	lenght = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		lenght++;
	}
	return (lenght);
}

/**
 * count_str - count the number of strings in a string array
 *
 * @stri: the string to be counted
 *
 * Return: the number of counted strings
 */
int count_str(char **stri)
{
	int i;

	i = 0;
	if (stri == NULL)
		return (i);
	for (i = 0; stri[i] != NULL; i++)
		;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: the string to be compared
 * @s2: the second string to be compared
 * Description:'A function'
 * Return: j if successful
 */
int _strcmp(const char *s1, const char *s2)
{
	int i, j;

	i = 0;
	j = 0;

	while (j == 0)
	{
		if ((*(s1 + i) == '\0') && (*(s2 + i) == '\0'))
			break;
		j = *(s1 + i) - *(s2 + i);
		i++;
	}
	return (j);
}
/**
 * *_strcat - it concatenates one string onto another
 * Description:'A function that replicates strncat'
 * @src: the string to be appended
 * @dest: the destination
 * Return: 'dest' if successful
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	i = 0;

	while (dest[i] != '\0')
		i++;
	j = 0;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
