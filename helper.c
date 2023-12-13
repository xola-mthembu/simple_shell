#include "shell.h"

/**
 * tokenizer - tokenizes input and stores it into an array
 * @input_string: input to be parsed
 * @delim: delimiter to be used, needs to be one character string
 * Return: array of tokens
 */
char **tokenizer(char *input_string, char *delim)
{
	int num_delim = 0;	/* Number of delimiters found */
	char **av = NULL;	/* Array of tokens */
	char *token = NULL;	/* Individual token */
	char *save_ptr = NULL;	/* For strtok_r to save its state */

	/* Initialize tokenization */
	token = _strtok_r(input_string, delim, &save_ptr);

	/* Tokenize until end of string */
	while (token != NULL)
	{
		av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
		av[num_delim] = token;
		token = _strtok_r(NULL, delim, &save_ptr);
		num_delim++;
	}

	/* Null-terminate the array of tokens */
	av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
	av[num_delim] = NULL;

	return (av);
}

/**
 * print - prints a string to stdout
 * @string: string to be printed
 * @stream: stream to print out to
 * Return: void
 */
void print(char *string, int stream)
{
	int i = 0;
	/* Loop through the string and write each character */
	for (; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}

/**
 * remove_newline - removes new line from a string
 * @str: string to be used
 * Return: void
 */
void remove_newline(char *str)
{
	int i = 0;
	/* Loop until newline or end of string is found */
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	/* Replace newline with null character */
	str[i] = '\0';
}

/**
 * _strcpy - copies a string to another buffer
 * @source: source to copy from
 * @dest: destination to copy to
 * Return: void
 */
void _strcpy(char *source, char *dest)
{
	int i = 0;
	/* Loop through source and copy each character to destination */
	for (; source[i] != '\0'; i++)
		dest[i] = source[i];
	/* Null-terminate the destination string */
	dest[i] = '\0';
}

/**
 * _strlen - counts string length
 * @string: string to be counted
 * Return: length of the string
 */
int _strlen(char *string)
{
	int len = 0;
	/* Check for NULL string */
	if (string == NULL)
		return (len);
	/* Loop through the string to count its length */
	for (; string[len] != '\0'; len++)
		;
	return (len);
}


