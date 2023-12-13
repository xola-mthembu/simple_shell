#include "shell.h"

/**
 * print_to_stderr - Outputs a string to standard error
 * @str: String to be printed
 * Return: Void
 */
void print_to_stderr(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		write_char_to_stderr(str[index]);
		index++;
	}
}

/**
 * write_char_to_stderr - Writes a character to standard error
 * @character: Character to write
 * Return: 1 on success, -1 on error with errno set
 */
int write_char_to_stderr(char character)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUFFER_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(STDERR_FILENO, buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[buffer_index++] = character;
	return (1);
}

/**
 * write_char_fd - Writes a character to a specified file descriptor
 * @character: Character to write
 * @file_descriptor: File descriptor to write to
 * Return: 1 on success, -1 on error with errno set
 */
int write_char_fd(char character, int file_descriptor)
{
	static int buffer_index;
	static char buffer[WRITE_BUF_SIZE];

	if (character == BUFFER_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buffer, buffer_index);
		buffer_index = 0;
	}
	if (character != BUFFER_FLUSH)
		buffer[buffer_index++] = character;
	return (1);
}

/**
 * print_string_fd - Outputs a string to a specified file descriptor
 * @str: String to be printed
 * @file_descriptor: File descriptor to write to
 * Return: Number of characters written
 */
int print_string_fd(char *str, int file_descriptor)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += write_char_fd(*str++, file_descriptor);
	}
	return (count);
}

