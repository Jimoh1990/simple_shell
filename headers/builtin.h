#ifndef BUILTIN_H
#define BUILTIN_H
#include "./list.h"

typedef int exit_status;
typedef struct state state;
typedef struct builtin builtin;
typedef exit_status(*builtincmd)(state *, char **);

/**
 * struct state - useful variables that would be passed
 * around from the main function.
 *
 * @env: shell environment variables
 * @aliases: shell aliases
 * @content: the contents to be interpreted by the commandline
 * @lines: an array of lines found in contents
 * @parts: an array of different parts of a line separated
 * by semicolon
 * @tokens: an array of tokens found in a line/part
 * @_errno: a number indicating the error of the last command ran
 * @lineno: the current line number
 * @fd: open file descriptor where commands are read from
 * @prog: the program name used to start the shell
 * @pid_buf: a buffer that'll be used to hold the program's pid
 * @errno_buf: a buffer that'll be used to hold the program's errno
 * @pid: the process ID of the shell
 */
struct state
{
	int lineno;
	int _errno;
	int fd;
	char *prog;
	char *pid_buf;
	char *errno_buf;
	char *content;
	char **lines;
	char **parts;
	char **tokens;
	node *env;
	node *aliases;
};


/**
 * struct builtin - a shell builtin
 *
 * @name: the name of the builtin
 * @handler: a function that handles the builtin command
 */
struct builtin
{
	char *name;
	builtincmd handler;
};

exit_status shellexit(state *self, char **arguments);
exit_status shellenv(state *self, char **arguments);
exit_status shellsetenv(state *self, char **arguments);
exit_status shellunsetenv(state *self, char **arguments);
exit_status shellcd(state *self, char **arguments);
exit_status shellalias(state *self, char **arguments);

#endif
