#include "shell.h"

/**
 * initializer - starts executing everything
 * @current_command: try to check current token
 * @type_command: parse token
 *
 * Return: void function
 */

void initializer(char **current_command, int type_command)
{
	pid_t PID; /* Process ID for the forked process */

	/* Check if the command is external or in PATH */
	if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
	{
		PID = fork(); /* Fork a new process */
		if (PID == 0) /* Child process */
			execute_command(current_command, type_command);
		else /* Parent process */
		{
			waitpid(PID, &status, 0); /* Wait for child to terminate */
			status >>= 8; /* Right-shift status to get exit code */
		}
	}
	else /* For built-in commands */
		execute_command(current_command, type_command);
}


