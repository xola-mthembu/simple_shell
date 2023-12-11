#include "shell.h"

/**
 * free_resources - Frees allocated resources
 * @line: Pointer to the buffer to be freed
 */
void free_resources(char *line)
{
	if (line != NULL)
		free(line);
}

