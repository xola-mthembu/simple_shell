#include "shell.h"

/**
 * env - Prints the current environment variables.
 * @tokenized_command: Command entered (unused in this function).
 * Return: void
 */
void env(char **tokenized_command __attribute__((unused)))
{
	int i;

	/* Loop through and print all environment variables. */
	for (i = 0; environ[i] != NULL; i++)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
}

/**
 * quit - Exits the shell.
 * @tokenized_command: Command entered.
 * Return: void
 */
void quit(char **tokenized_command)
{
	int num_token = 0, arg;

	/* Count the number of tokens in the command. */
	for (; tokenized_command[num_token] != NULL; num_token++)
		;

	/* If only 'exit' is entered, exit with last status. */
	if (num_token == 1)
	{
		free(tokenized_command);
		free(line);
		free(commands);
		exit(status);
	}
	/* If 'exit' is followed by an argument, process it. */
	else if (num_token == 2)
	{
		arg = _atoi(tokenized_command[1]);
		/* Check if the argument is an illegal number. */
		if (arg == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(tokenized_command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else  /* Exit with the given argument. */
		{
			free(line);
			free(tokenized_command);
			free(commands);
			exit(arg);
		}
	}
	else  /* If 'exit' is followed by more than one argument. */
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
}


