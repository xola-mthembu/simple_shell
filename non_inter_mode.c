#include "shell.h"

/**
 * non_interactive - handles non_interactive mode
 * Return: void
 */
void non_interactive(void)
{
	char **current_command = NULL;  /* Stores each command */
	int i, type_command = 0;        /* Loop index, command type */
	size_t n = 0;                   /* Size for getline */

	/* Check if in non-interactive mode */
	if (!(isatty(STDIN_FILENO)))
	{
		/* Read lines from stdin */
		while (getline(&line, &n, stdin) != -1)
		{
			remove_newline(line);    /* Remove newlines */
			remove_comment(line);    /* Remove comments */
			commands = tokenizer(line, ";");  /* Tokenize by ";" */

			/* Process each command */
			for (i = 0; commands[i] != NULL; i++)
			{
				current_command = tokenizer(commands[i], " ");
				if (current_command[0] == NULL)
				{
					free(current_command);
					break;
				}
				type_command = parse_command(current_command[0]);
				initializer(current_command, type_command);
				free(current_command);
			}
			free(commands);
		}
		free(line);  /* Free the line buffer */
		exit(status);
	}
}


