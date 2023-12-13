#include "shell.h"

/**
 *_strtok_r - tokenizes a string
 *@string: string to be tokenized
 *@delim: delimiter to tokenize
 *@save_ptr: ptr for next token
 *Return: The next available token
 */
char *_strtok_r(char *string, char *delim, char **save_ptr)
{
	char *finish;	/* Pointer to the end of the token */

	/* Initialize string from save_ptr if null */
	if (string == NULL)
		string = *save_ptr;

	/* Return NULL if string is empty */
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	/* Skip leading delimiters */
	string += _strspn(string, delim);

	/* Return NULL if string is empty */
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}

	/* Find the end of the token */
	finish = string + _strcspn(string, delim);

	/* Handle end of string */
	if (*finish == '\0')
	{
		*save_ptr = finish;
		return (string);
	}

	/* Null-terminate and update save_ptr */
	*finish = '\0';
	*save_ptr = finish + 1;
	return (string);
}

/**
 * _atoi - changes a string to an integer
 * @s: the string
 * Return: the converted int
 */
int _atoi(char *s)
{
	unsigned int n = 0;	/* To hold the converted number */

	/* Loop through the string to convert it to an integer */
	do {
		/* Handle special characters */
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		/* Convert number */
		else if (*s >= '0' && *s <= '9')
			n = (n * 10) + (*s - '0');
		/* Exit if a number has been formed */
		else if (n > 0)
			break;
	} while (*s++);
	return (n);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: old pointer
 * @old_size: old size
 * @new_size: new size
 * Return: new pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *temp_block;	/* Temporary block for reallocation */
	unsigned int i;	/* Loop index */

	/* Handle NULL pointers */
	if (ptr == NULL)
	{
		temp_block = malloc(new_size);
		return (temp_block);
	}
	/* Return the same pointer if sizes are equal */
	else if (new_size == old_size)
		return (ptr);
	/* Free memory if new size is zero */
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	/* Reallocate memory */
	else
	{
		temp_block = malloc(new_size);
		if (temp_block != NULL)
		{
			/* Copy old data */
			for (i = 0; i < min(old_size, new_size); i++)
				*((char *)temp_block + i) = *((char *)ptr + i);
			free(ptr);
			return (temp_block);
		}
		else
			return (NULL);
	}
}

/**
 * ctrl_c_handler - handles CTRL-C
 * @signum: signal number
 * Return: void
 */
void ctrl_c_handler(int signum)
{
	/* Check for SIGINT (Ctrl-C) */
	if (signum == SIGINT)
		print("\n($) ", STDIN_FILENO);
}

/**
 * remove_comment - removes comments
 * @input: input
 * Return: void
 */
void remove_comment(char *input)
{
	int i = 0;	/* Loop index */

	/* Null-terminate if comment starts at beginning */
	if (input[i] == '#')
		input[i] = '\0';

	/* Find '#' and null-terminate the string */
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}


