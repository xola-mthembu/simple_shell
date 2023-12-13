#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

/**
 * execute_command - Executes a command with arguments
 * @argv: Argument vector for the command to execute
 *
 * Return: void
 */
void execute_command(char *argv[])
{
	if (fork() == 0)
	{
		/* Child process */
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("./shell_v0.2");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		wait(&status);
	}
}

/**
 * main - Entry point for the simple shell 0.2
 *
 * Description: Extend the simple shell to handle command lines with arguments.
 * Parses the input and executes the command with the given arguments.
 *
 * Return: 0 on successful execution, or error code on failure.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[MAX_ARGS];
	char *token;
	int i;

	while (1)
	{
		printf("#cisfun$ ");  /* Display the prompt */
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			break;  /* Handle EOF */

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';  /* Remove newline character */

		/* Tokenize the input */
		token = strtok(command, " ");
		i = 0;

		while (token != NULL && i < MAX_ARGS)
		{
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;  /* Null-terminate the arguments list */

		execute_command(argv);
	}

	return (0);
}
