#include "shell.h"

/**
 * appendStr - append a string to an array of strings
 *
 * @arr: a pointer to a malloced array of strings
 * @size: a pointer to an integer holding the size of the array
 * @str: the new string to append to the array
 * @index: the index at which to insert the string
 *
 * Return: 1 if succeeded, or 0 if it failed
 */
bool appendStr(char ***arr, size_t *size, char *str, int index)
{
	size_t arr_size;
	char **array;

	arr_size = *size;
	array = *arr;

	if (!(arr && *arr))
		return (false);
	while (arr_size <= (unsigned int)index)
	{
		if (arr_size == 0)
			arr_size++;
		array = _realloc(array,
			NPTRS(arr_size),
			NPTRS(arr_size) * 2);
		arr_size *= 2;
		if (!array)
			return (false);
	}
	(array)[index] = str;
	*arr = array;
	*size = arr_size;
	return (true);
}

/**
 * appendChar - appends a character to a string
 *
 * @string: a pointer to malloced string
 * @size: a pointer to an integer holding the size of the string
 * @chr: the character to add to the string
 * @index: the index at which to insert the character
 *
 * Return: 1 if succeeded, or 0 if it failed
 */
bool appendChar(char **string, size_t *size, char chr, int index)
{
	size_t buf_size;
	char *buf;

	if (!(string && *string))
		return (false);

	if (size == NULL)
		for (buf_size = 0; (*string)[buf_size]; buf_size++)
			continue;
	else
		buf_size = *size;
	buf = *string;

	while (buf_size <= (unsigned int)index)
	{
		if (buf_size == 0)
			buf_size++;
		buf = _realloc(buf, buf_size, buf_size * 2);
		buf_size *= 2;
		if (!buf)
			return (false);
	}
	buf[index] = chr;
	*string = buf;
	if (size != NULL)
		*size = buf_size;
	return (true);
}

/**
 * appendInt - appends an integer to a string
 *
 * @string: a pointer to malloced string
 * @size: a pointer to an integer holding the size of the string
 * @num: the integer to insert
 * @index: the index at which to insert the character
 *
 * Return: number of digits appended.
 *		-1 is return if appendChar failed.
 */
int appendInt(char **string, size_t *size, int num, int index)
{
	int len = 0;

	if (num < 0)
	{
		appendChar(string, size, '-', index + len);
		num *= -1;
		len++;
	}
	if (num < 10)
		return (len + appendChar(string, size, ('0' + num), index + len));
	len += appendInt(string, size, num / 10, index + len);
	len += appendChar(string, size, (num % 10) + '0', index + len);
	return (len);
}
