#ifndef SHELL_H	/* Include guard to prevent double inclusion of this header. */
#define SHELL_H

#include <stdio.h>	/* Standard I/O functions. */
#include <stdlib.h>	/* Standard library functions like malloc and free. */
#include <string.h>	/* String manipulation functions. */
#include <sys/types.h>	/* System types. */
#include <sys/wait.h>	/* wait() function. */
#include <sys/stat.h>	/* stat() function. */
#include <unistd.h>	/* UNIX Standard functions. */
#include <errno.h>	/* Error numbers. */
#include <dirent.h>	/* Directory entries. */
#include <signal.h>	/* Signal handling. */

/* Constants for command types. */
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

/* Macro to find minimum of x and y. */
#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 * struct map - Maps a command name to a function.
 * @command_name: Name of the command.
 * @func: Function that executes the command.
 */
typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **environ;	/* Environment variables. */
extern char *line;	/* Input line from shell. */
extern char **commands;	/* Array of parsed commands. */
extern char *shell_name;	/* Name of the shell executable. */
extern int status;	/* Exit status of the last command. */

/* Helper function prototypes. */
void print(char *, int);
char **tokenizer(char *, char *);
void remove_newline(char *);
int _strlen(char *);
void _strcpy(char *, char *);

/* More helper function prototypes. */
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);

/* Additional helper function prototypes. */
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int);
void remove_comment(char *);

/* Core utility function prototypes. */
int parse_command(char *);
void execute_command(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);

/* Functions for internal commands. */
void env(char **);
void quit(char **);

/* Main utility functions. */
extern void non_interactive(void);
extern void initializer(char **current_command, int type_command);

#endif	/* End of include guard. */


