#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define MAX_PATH_LENGTH 1024

/**
 * execute_command - Searches for and executes a command in the PATH
 * @command: The command to execute
 * @argv: Argument vector for the command to execute
 * @envp: Environment variables
 *
 * Return: void. Exits with EXIT_FAILURE if command execution fails.
 */
void execute_command(char *command, char *argv[], char **envp)
{
	char *path = getenv("PATH");
	char full_command[MAX_PATH_LENGTH];
	char *path_token = strtok(path, ":");

	while (path_token != NULL)
	{
		snprintf(full_command, MAX_PATH_LENGTH, "%s/%s", path_token, command);
		if (access(full_command, X_OK) == 0)
		{
			argv[0] = full_command;
			execve(full_command, argv, envp);
		}
		path_token = strtok(NULL, ":");
	}

	fprintf(stderr, "%s: command not found\n", command);
	exit(EXIT_FAILURE);
}

/**
 * main - Entry point for the simple shell 0.3
 * Description: Extend the simple shell to handle the PATH environment var.
 * Parses the input and searches for executables in the PATH before executing.
 * Does not call fork if the command doesn’t exist.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @envp: Environment variables.
 * Return: 0 on successful execution, or error code on failure.
 */
int main(int argc, char **argv, char **envp)
{
	char command[MAX_COMMAND_LENGTH];
	char *command_argv[MAX_ARGS];
	char *token;
	int i, status;

	/* Casting argc and argv to void to indicate intentional unused */
	(void)argc;
	(void)argv;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			break;

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';

		token = strtok(command, " ");
		for (i = 0; token != NULL && i < MAX_ARGS; i++)
		{
			command_argv[i] = token;
			token = strtok(NULL, " ");
		}
		command_argv[i] = NULL;

		if (command_argv[0] == NULL)
			continue;

		if (fork() == 0)
			execute_command(command_argv[0], command_argv, envp);
		else
			wait(&status);
	}
	return (0);
}
