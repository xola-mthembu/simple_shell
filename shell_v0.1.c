#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

/**
 * execute_command - Executes a single-word command
 * @command: The command to execute
 *
 * Return: void
 */
void execute_command(char *command)
{
	char *argv[2];
	int status;

	argv[0] = command; /* Set up arguments for execve */
	argv[1] = NULL;

	if (fork() == 0)
	{
		/* Child process */
		if (execve(command, argv, NULL) == -1)
		{
			perror("./shell_v0.1");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(&status);
	}
}
/**
 * main - Entry point for the simple shell 0.1
 *
 * Description: A simple UNIX command interpreter that reads single-word
 * commands from standard input and executes them. It handles the EOF
 * condition and prints an error if the command is not found.
 *
 * Return: 0 on successful execution, or error code on failure.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("#cisfun$ ");  /* Display the prompt */
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			break;  /* Handle EOF */

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';  /* Remove newline character */

		/* Handling single-word commands only */
		if (strchr(command, ' ') != NULL)
		{
			printf("%s: No such file or directory\n", command);
			continue;
		}

		execute_command(command);
	}

	return (0);
}
