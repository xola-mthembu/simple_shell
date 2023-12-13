#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

/**
 * main - Entry point for the simple shell
 *
 * Description: A simple UNIX command interpreter that reads commands from
 * standard input and executes them. The shell runs in a loop, displaying
 * a prompt and waiting for user input. It handles single-word commands
 * without arguments. When EOF (Ctrl+D) is encountered, the shell exits.
 *
 * Return: 0 on successful execution, or error code on failure.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *argv[2];
	int status;

	while (1)
	{
		printf("#cisfun$ ");  /* Display the prompt */
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			break;  /* Handle EOF */

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';  /* Remove newline character */

		argv[0] = command;  /* Set up arguments for execve */
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

	return (0);
}
