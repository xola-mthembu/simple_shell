#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

ssize_t read_line(char **lineptr, size_t *n, FILE *stream);
int execute_command(char *cmd);
void free_resources(char *line);

#endif /* SHELL_H */

