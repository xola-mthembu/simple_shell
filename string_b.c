#include "shell.h"

/**
 * copy_string - copies a string from source to destination
 * @target: destination string
 * @source: source string
 * Return: pointer to the target string
 */
char *copy_string(char *target, char *source)
{
	int index = 0;

	if (target == source || source == NULL)
		return target;
	while (source[index])
	{
		target[index] = source[index];
		index++;
	}
	target[index] = '\0';
	return target;
}

/**
 * duplicate_string - creates a duplicate of the given string
 * @original: string to duplicate
 * Return: pointer to the new string, or NULL on failure
 */
char *duplicate_string(const char *original)
{
	int len = 0;
	char *duplicate;

	if (!original)
		return NULL;
	while (original[len])
		len++;
	duplicate = malloc(sizeof(char) * (len + 1));
	if (!duplicate)
		return NULL;
	for (int i = 0; i <= len; i++)
		duplicate[i] = original[i];
	return duplicate;
}

/**
 * output_string - outputs a string to stdout
 * @str: string to output
 * Return: None
 */
void output_string(char *str)
{
	if (!str)
		return;
	while (*str)
		_output_char(*str++);
}

/**
 * _output_char - outputs a single character to stdout
 * @char_to_print: character to output
 * Return: 1 on success, -1 on error
 */
int _output_char(char char_to_print)
{
	static int buf_index = 0;
	static char buffer[WRITE_BUF_SIZE];

	if (char_to_print == BUF_FLUSH || buf_index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, buf_index);
		buf_index = 0;
	}
	if (char_to_print != BUF_FLUSH)
		buffer[buf_index++] = char_to_print;
	return 1;
}

