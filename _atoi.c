#include "shell.h"

/**
 * shell_interactive - checks if shell is in interactive mode
 * @info: pointer to struct containing shell info
 *
 * Return: 1 if interactive, 0 otherwise
 */
int shell_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * char_is_delimiter - checks if a character is a delimiter
 * @character: character to check
 * @delimiters: string containing delimiter characters
 * Return: 1 if true, 0 if false
 */
int char_is_delimiter(char character, char *delimiters)
{
	while (*delimiters)
		if (character == *delimiters++)
			return (1);
	return (0);
}

/**
 * is_letter - checks for an alphabetic character
 * @ch: character to check
 * Return: 1 if alphabetic, 0 otherwise
 */
int is_letter(int ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 * str_to_int - converts a string to an integer
 * @str: string to convert
 * Return: integer value of string
 */
int str_to_int(char *str)
{
	int index = 0, sign = 1, started = 0;
	unsigned int number = 0;

	for (; str[index] != '\0' && started != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			started = 1;
			number = number * 10 + (str[index] - '0');
		}
		else if (started == 1)
			started = 2;
	}

	return (sign == -1 ? -number : number);
}

