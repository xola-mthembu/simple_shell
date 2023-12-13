#include "shell.h"

char **commands = NULL;	/* Stores command tokens */
char *line = NULL;		/* Stores input line */
char *shell_name = NULL;	/* Stores name of the shell */
int status = 0;			/* Exit status */

/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 *
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char **current_command = NULL;	/* Current command */
	int i, type_command = 0;		/* Loop index, cmd type */
	size_t n = 0;				/* Size for getline */

	signal(SIGINT, ctrl_c_handler);		/* Handle Ctrl-C */
	shell_name = argv[0];			/* Store shell name */

	while (1)
	{
		non_interactive();		/* Handle non-interactive mode */
		print(" ($) ", STDOUT_FILENO);	/* Display shell prompt */
		if (getline(&line, &n, stdin) == -1)
		{
			free(line);		/* Free line buffer */
			exit(status);		/* Exit */
		}
		remove_newline(line);		/* Remove newline */
		remove_comment(line);		/* Remove comments */
		commands = tokenizer(line, ";");	/* Tokenize input */

		for (i = 0; commands[i] != NULL; i++)	/* Loop through cmds */
		{
			current_command = tokenizer(commands[i], " ");
			if (current_command[0] == NULL)
			{
				free(current_command);	/* Free empty cmd */
				break;
			}
			type_command = parse_command(current_command[0]); /* Get cmd type */
			initializer(current_command, type_command);	/* Init and exec cmd */
			free(current_command);	/* Free cmd memory */
		}
		free(commands);		/* Free commands array */
	}
	free(line);		/* Free line buffer */
	return (status);	/* Return exit status */
}


