#include "shell.h"

/**
 * calculate_length - calculates the length of a string
 * @str: string to calculate the length of
 * Return: length of the string as an integer
 */
int calculate_length(char *str)
{
	int len = 0;
	if (!str)
		return 0;

	while (*str++)
		len++;
	return len;
}

/**
 * compare_strings - compares two strings lexicographically
 * @first: first string for comparison
 * @second: second string for comparison
 * Return: int indicating the result of comparison
 */
int compare_strings(char *first, char *second)
{
	while (*first && *second)
	{
		if (*first != *second)
			return (*first - *second);
		first++, second++;
	}
	return (*first ? 1 : (*second ? -1 : 0));
}

/**
 * check_prefix - checks if the string starts with a given prefix
 * @string: string to be checked
 * @prefix: prefix to look for
 * Return: pointer to the character in string after the prefix, or NULL
 */
char *check_prefix(const char *string, const char *prefix)
{
	while (*prefix)
	{
		if (*prefix != *string)
			return NULL;
		prefix++, string++;
	}
	return (char *)string;
}

/**
 * append_string - appends one string to another
 * @destination: buffer where the string is appended
 * @source: string to append
 * Return: pointer to the concatenated string
 */
char *append_string(char *destination, char *source)
{
	char *original_dest = destination;

	while (*destination)
		destination++;
	while ((*destination++ = *source++))
		;

	return original_dest;
}

