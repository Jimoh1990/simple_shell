#include "shell.h"
#include <stdarg.h>

/**
 * printerr - print an error message to stderr
 *
 * @message: the message to print
 *
 * Return: nothing
 */
void printerr(const char *message)
{
	write(STDERR_FILENO, message, _strlen(message));
}



/**
 * printout - prints a message to stdout
 *
 * @message: the message to print
 *
 * Return: nothing
 */
void printout(const char *message)
{
	write(STDOUT_FILENO, message, _strlen(message));
}

/**
 * fprinterr - print an error message to stderr
 *
 * @message: the message to print
 *
 * Return: nothing
 */
void fprinterr(char *message)
{
	write(STDERR_FILENO, message, _strlen(message));
	free(message);
}



/**
 * fprintout - prints a message to stdout
 *
 * @message: the message to print
 *
 * Return: nothing
 */
void fprintout(char *message)
{
	write(STDOUT_FILENO, message, _strlen(message));
	free(message);
}

/**
 * format - resolves format specifiers in a string
 * @fmt: the format string
 * Return: a new string with format specifiers replaced
 * with actual value
 */
char *format(const char *fmt, ...)
{
	char *buffer, chr, nxt, *s;
	size_t size;
	int buf_index, index, i;
	va_list args;

	if (!fmt || !fmt[0])
		return (NULL);

	size = 4;
	buffer = malloc(NCHARS(size));
	index = buf_index = 0;
	chr = fmt[index++];
	nxt = fmt[index];
	va_start(args, fmt);

	for (index = 0; fmt[index]; index++)
	{
		chr = fmt[index];
		nxt = fmt[index + 1];

		if (chr == '%')
		{
			if (nxt == 'd')
			{
				buf_index += appendInt(&buffer, &size, va_arg(args, int), buf_index);
			}
			else if (nxt == 's')
			{
				s = va_arg(args, char *);
				for (i = 0; s[i]; i++)
					appendChar(&buffer, &size, s[i], buf_index++);
			}
			index++;
		}
		else
			appendChar(&buffer, &size, chr, buf_index++);
	}
	va_end(args);
	appendChar(&buffer, &size, '\0', buf_index);
	return (buffer);
}
