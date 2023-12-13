#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

/**
 * main - Entry point for the simple shell 0.2
 * Description: Enhances the shell to handle command lines with arguments.
 *
 * Return: 0 on success, non-zero on error.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[MAX_ARGS];
	char *token;
	int i;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			continue;
		}

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';

		i = 0;
		token = strtok(command, " ");
		while (token != NULL && i < MAX_ARGS - 1)
		{
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		if (argv[0] != NULL)
			system(argv[0]);
	}

	return (0);
}
