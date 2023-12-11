#include "shell.h"

/**
 * main - Entry point for the simple shell
 * Description: A simple UNIX command interpreter
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = read_line(&line, &len, stdin);
		if (read == -1)
		{
			free_resources(line);
			return (feof(stdin) ? 0 : 1);
		}

		if (execute_command(line) == -1)
			perror("Error");

		free_resources(line);
	}
	return (0);
}

