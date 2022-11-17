#ifndef SHELL_H
#define SHELL_H
#define bool int
#define true 1
#define false 0
#define NPTRS(n) (n * sizeof(void *))
#define NCHARS(n) (n * sizeof(char))

#include "headers/include.h"
#include "headers/list.h"
#include "headers/string.h"
#include "headers/builtin.h"
#include "headers/path.h"

extern char **environ;

/* io */
void printerr(const char *message);
void printout(const char *message);
void fprinterr(char *message);
void fprintout(char *message);
void prompt(state *self);


/* quote */
int findquote(char *str, char quote);
void comment(char *string);
bool should_quote(const char *string);
char *remove_quotes(char *string);

/* line */
char *getlines(int fd);
char **split(char *string, char *delimiter,
		unsigned int max, bool group_quote);

/* find */
char *findcmd(const char *command, const char *PATH);
struct dirent *findfile(DIR *dir, const char *filename);
char *joinpath(const char *base, const char *child);

/* run */
int interactive(state *self);
int non_interactive(state *self, int fd);
int execute(const char *program, char **args, char **env);
int runline(state *self, char *line);
bool runbuiltin(state *self, char **arguments);
bool runprogram(state *self, char **arguments);
bool runalias(state *self, char **command);

/*tokenizefile*/
char ***tokenizefiles(char *line);
char **tokenizefile(char *line);
void replaceline(char *av[]);

/* append */
bool appendStr(char ***arr, size_t *size, char *str, int index);
bool appendChar(char **string, size_t *size, char chr, int index);
bool appendInt(char **string, size_t *size, int num, int index);

/*atoi*/
int checkatoi(char *s);
int _atoi(char *s);


/* format */
char *format(const char *fmt, ...);


/* main */
state *init(char *prog, char **env);
void deinit(state *self);
void cleanup(state *self);

/* replacement */
char *replace(state *self, char *var);

/* realloc */
void *_realloc(void *ptr, unsigned int osize, unsigned int nsize);

#endif
