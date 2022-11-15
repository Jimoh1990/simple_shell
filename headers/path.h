#ifndef PATH_H
#define PATH_H

bool ispath(const char *s);
char *joinpath(const char *base, const char *child);
char *basename(const char *path);
char *dirname(char *path);

#endif
