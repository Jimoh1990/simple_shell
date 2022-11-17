#include "shell.h"

/**
 * getlines - read all lines from stdin.
 *
 * Description: When file is terminal, this function
 * acts like getline(3), reading just one line.
 * When file is a pipe or regular file, all the content is
 * consumed at a go.
 *
 * @fd: the file descriptor
 *
 * Return: a buffer holding all contents of the file.
 * NULL is returned if malloc failed or if EOF is reached.
 */
char *getlines(int fd)
{
	char *buffer;
	size_t offset, size;
	int step;
	ssize_t bytesread;
	struct stat fdstat;

	fstat(fd, &fdstat);
	if (fdstat.st_size == 0)
		size = 1024;
	else
		size = fdstat.st_size + 1;
	buffer = malloc(size);
	offset = 0;
	step = size;

	if (!buffer)
		return (NULL);

	while (true)
	{
		bytesread = read(fd, &buffer[offset], step);
		if (bytesread == 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytesread < step)
			break;
		offset += step;
		buffer = _realloc(buffer, size, size + step);
		size += step;
		if (!buffer)
			return (NULL);
	}
	buffer[offset + bytesread - 1] = '\0';
	return (buffer);
}


/**
 * getLine - read a line from the stdin
 * Return: the line read from stdin, or NULL if EOF was encountered
 *
 * NOTE: the newline would not be include in the returned string
 */
char *getLine(void)
{
	int index;
	size_t bufsize;
	char *buffer;
	int c;

	bufsize = 2;
	buffer = malloc(bufsize);
	index = 0;

	if (buffer == NULL)
	{
		perror("Error");
		exit(errno);
	}
	c = fgetc(stdin);

	while (c != EOF)
	{
		if (c == '\n')
		{
			appendChar(&buffer, &bufsize, '\0', index);
			break;
		}
		appendChar(&buffer, &bufsize, c, index);
		index++;
		c = fgetc(stdin);
	}
	if (c == EOF)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

/**
 * split - split a string using a delimiter
 *
 * @string: the string to split
 *
 * @delimiter: a list of delimiters to use to split the string
 *
 * @max: the maximum number of times the string should be splitted
 * Set this to 0 to split infinitely
 *
 * @group_quote: text inside quote should be grouped as one token
 *
 * Return: A null-terminated array of strings.
 * NULL is returned if malloc failed or if the string
 * could not be split; this could be because:
 * - the string is empty
 * - the string is NULL
 * - the string only contains delimiters
 * - delimiters is NULL
 * - delimiters is empty
 */
char **split(char *string, char *delimiter, unsigned int max, bool group_quote)
{
	char **array, prev = '\0', curr;
	size_t arr_size = 2;
	unsigned int arr_ind = 0, str_ind, i;
	bool flipped;
	int quote_index;

	if (!(string && *string && delimiter && *delimiter))
		return (NULL);
	array = malloc(NPTRS(arr_size));
	for (str_ind = 0; string[str_ind]; str_ind++)
	{
		curr = string[str_ind];
		flipped = false;
		for (i = 0; delimiter[i]; i++)
			if (curr == delimiter[i])
			{
				string[str_ind] = '\0';
				flipped = true;
				break;
			}
		if (prev == '\0' && flipped == false)
			appendStr(&array, &arr_size, &string[str_ind], arr_ind++);
		if (group_quote && (!flipped && (curr == '\'' || curr == '"')))
		{
			quote_index = findquote(string + str_ind + 1, curr);
			if (quote_index != -1)
				str_ind += quote_index + 1;
		}
		if (max && max + 1 == arr_ind)
			break;
		prev = string[str_ind];
	}
	if (arr_ind)
		appendStr(&array, &arr_size, NULL, arr_ind);
	else
	{
		free(array);
		array = NULL;
	}
	return (array);
}

