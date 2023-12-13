#include "shell.h"

/**
 * read_line - Reads a line from stdin
 * @lineptr: Pointer to the buffer
 * @n: Buffer size
 * @stream: File stream to read from
 * Return: Number of characters read
 */
ssize_t read_line(char **lineptr, size_t *n, FILE *stream)
{
	return (getline(lineptr, n, stream));
}

