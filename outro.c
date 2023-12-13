#include "shell.h"

/**
 * copy_string_n - Copies a string with a limit on characters
 * @destination: Buffer to copy the string into
 * @source: Source string to copy
 * @limit: Maximum number of characters to copy
 * Return: Pointer to the destination string
 */
char *copy_string_n(char *destination, char *source, int limit)
{
	int src_idx = 0, dest_idx;
	char *dest_pointer = destination;

	while (source[src_idx] != '\0' && src_idx < limit - 1)
	{
		destination[src_idx] = source[src_idx];
		src_idx++;
	}
	for (dest_idx = src_idx; dest_idx < limit; dest_idx++)
		destination[dest_idx] = '\0';

	return (dest_pointer);
}

/**
 * concatenate_strings_n - Concatenates two strings with a length limit
 * @first_str: The first string to be concatenated
 * @second_str: The second string to append
 * @max_length: Maximum number of bytes to use from the second string
 * Return: Pointer to the concatenated string
 */
char *concatenate_strings_n(char *first_str, char *second_str, int max_length)
{
	int first_len = 0, second_idx = 0;
	char *first_ptr = first_str;

	while (first_str[first_len] != '\0')
		first_len++;
	while (second_str[second_idx] != '\0' && second_idx < max_length)
	{
		first_str[first_len++] = second_str[second_idx++];
	}
	if (second_idx < max_length)
		first_str[first_len] = '\0';

	return (first_ptr);
}

/**
 * find_char_in_string - Locates a character in a string
 * @str: String to search
 * @char_to_find: Character to find in the string
 * Return: Pointer to the location of the character in the string, or NULL
 */
char *find_char_in_string(char *str, char char_to_find)
{
	while (*str)
	{
		if (*str == char_to_find)
			return (str);
		str++;
	}
	return (NULL);
}

