#include "shell.h"

/**
 * execute_command - Executes a command
 * @cmd: Command to execute
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *cmd)
{
	pid_t pid;
	int status;
	char *argv[2];

	cmd[strcspn(cmd, "\n")] = '\0'; /* Remove newline at end */
	argv[0] = cmd;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(argv[0], argv, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Error forking */
		return (-1);
	}
	else
	{
		/* Parent process */
		wait(&status);
	}
	return (0);
}

