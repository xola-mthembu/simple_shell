#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10
#define MAX_PATH_LENGTH 1024

/**
 * execute_command - Executes a command found in the PATH
 * @command: The command to execute
 * @argv: Argument vector for the command
 * @envp: Environment variables
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
 * print_env - Prints the current environment variables
 * @envp: Environment variables
 */
void print_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp++);
	}
}

/**
 * handle_command - Reads a command and executes it
 * @command: The command to handle
 * @envp: Environment variables
 */
void handle_command(char *command, char **envp)
{
	char *command_argv[MAX_ARGS];
	char *token;
	int i, status;

	token = strtok(command, " ");
	for (i = 0; token != NULL && i < MAX_ARGS; i++)
	{
		command_argv[i] = token;
		token = strtok(NULL, " ");
	}
	command_argv[i] = NULL;

	if (strcmp(command_argv[0], "env") == 0)
	{
		print_env(envp);
	}
	else if (strcmp(command_argv[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (fork() == 0)
		{
			execute_command(command_argv[0], command_argv, envp);
		}
		else
		{
			wait(&status);
		}
	}
}

/**
 * main - Entry point of the shell
 * Description: Extends the shell to include 'env' command.
 * Reads and executes commands, and handles 'env' and 'exit'.
 *
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 * Return: 0 on success, error code on failure
 */
int main(int argc, char **argv, char **envp)
{
	char command[MAX_COMMAND_LENGTH];

	(void)argc;  /* Unused parameter */
	(void)argv;  /* Unused parameter */

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0';

		handle_command(command, envp);
	}

	return (0);
}
