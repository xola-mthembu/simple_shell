#include "shell.h"

/**
 * string_to_error_int - Converts a string to an integer with error handling
 * @str: The string to be converted
 * Return: The converted integer or -1 on error
 */
int string_to_error_int(char *str)
{
	int index = 0;
	unsigned long int num_result = 0;

	if (*str == '+')
		str++;
	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			num_result = num_result * 10 + (str[index] - '0');
			if (num_result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (num_result);
}

/**
 * output_error_message - Outputs an error message
 * @info: Information struct with error details
 * @error_string: String containing the specific error type
 */
void output_error_message(info_t *info, char *error_string)
{
	write_to_stderr(info->fname);
	write_to_stderr(": ");
	output_decimal(info->line_count, STDERR_FILENO);
	write_to_stderr(": ");
	write_to_stderr(info->argv[0]);
	write_to_stderr(": ");
	write_to_stderr(error_string);
}

/**
 * output_decimal - Prints a decimal number to a specified file descriptor
 * @number: The number to print
 * @file_descriptor: The file descriptor to write to
 * Return: Number of characters printed
 */
int output_decimal(int number, int file_descriptor)
{
	int (*char_writer)(char) = write_char_fd;
	int digit, char_count = 0;
	unsigned int abs_number, current;

	if (file_descriptor == STDERR_FILENO)
		char_writer = write_char_to_stderr;
	if (number < 0)
	{
		abs_number = -number;
		char_writer('-');
		char_count++;
	}
	else
		abs_number = number;
	current = abs_number;
	for (digit = 1000000000; digit > 1; digit /= 10)
	{
		if (abs_number / digit)
		{
			char_writer('0' + current / digit);
			char_count++;
		}
		current %= digit;
	}
	char_writer('0' + current);
	char_count++;

	return (char_count);
}

/**
 * number_to_string - Converts a number to a string representation
 * @number: The number to convert
 * @base: The numerical base for conversion
 * @flags: Flags indicating conversion options
 * Return: Pointer to the converted string
 */
char *number_to_string(long int number, int base, int flags)
{
	static char *num_chars;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	num_chars = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = num_chars[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * strip_comments - Removes comments from a string
 * @buffer: String to be processed
 * Return: Void
 */
void strip_comments(char *buffer)
{
	int idx;

	for (idx = 0; buffer[idx] != '\0'; idx++)
		if (buffer[idx] == '#' && (idx == 0 || buffer[idx - 1] == ' '))
		{
			buffer[idx] = '\0';
			break;
		}
}

