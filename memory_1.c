#include "shell.h"

/**
 * safe_free - safely frees memory and sets pointer to NULL
 * @address: the address of the pointer to be freed
 * Return: 1 if memory was freed, 0 if not
 */
int safe_free(void **address)
{
	if (address && *address)
	{
		free(*address);
		*address = NULL;
		return (1);  // Indicates successful freeing of memory
	}
	return (0);  // Indicates no action was taken
}

