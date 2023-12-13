#include "shell.h"

/**
 * buffer_input - Handles input buffering for chained commands
 * @info: Struct containing shell information
 * @buffer: Pointer to the input buffer
 * @length: Pointer to the length variable
 * Return: Number of bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
	ssize_t read_bytes = 0;
	size_t len_placeholder = 0;

	if (!*length) /* Check if buffer needs refilling */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
		read_bytes = custom_getline(info, buffer, &len_placeholder);
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0'; // Remove newline
				read_bytes--;
			}
			info->linecount_flag = 1;
			filter_out_comments(*buffer);
			append_to_history(info, *buffer, info->histcount++);
			*length = read_bytes;
			info->cmd_buffer = buffer;
		}
	}
	return (read_bytes);
}

/**
 * fetch_line_input - Retrieves a line of input, excluding newline
 * @info: Struct containing shell information
 * Return: Number of bytes read
 */
ssize_t fetch_line_input(info_t *info)
{
	static char *chain_buffer;
	static size_t buf_idx, next_idx, buf_len;
	ssize_t read_result = 0;
	char **buffer_pointer = &(info->arg), *current_pointer;

	flush_output();
	read_result = buffer_input(info, &chain_buffer, &buf_len);
	if (read_result == -1) // End of File (EOF)
		return (-1);

	if (buf_len)
	{
		next_idx = buf_idx;
		current_pointer = chain_buffer + buf_idx;

		process_command_chain(info, chain_buffer, &next_idx, buf_idx, buf_len);
		while (next_idx < buf_len)
		{
			if (is_command_chain(info, chain_buffer, &next_idx))
				break;
			next_idx++;
		}

		buf_idx = next_idx + 1;
		if (buf_idx >= buf_len)
			buf_idx = buf_len = 0;

		*buffer_pointer = current_pointer;
		return (string_length(current_pointer));
	}

	*buffer_pointer = chain_buffer;
	return (read_result);
}

/**
 * fetch_buffer - Reads a buffer of data
 * @info: Struct containing shell information
 * @buffer: Buffer to read into
 * @index: Current index in the buffer
 * Return: Number of bytes read
 */
ssize_t fetch_buffer(info_t *info, char *buffer, size_t *index)
{
	ssize_t read_result = 0;

	if (*index)
		return (0);
	read_result = read(info->readfd, buffer, READ_BUF_SIZE);
	if (read_result >= 0)
		*index = read_result;
	return (read_result);
}

/**
 * custom_getline - Retrieves the next line of input from stdin
 * @info: Struct containing shell information
 * @buffer_ptr: Address of the buffer pointer
 * @buffer_len: Size of the preallocated buffer, if not NULL
 * Return: Number of bytes read
 */
int custom_getline(info_t *info, char **buffer_ptr, size_t *buffer_len)
{
	static char internal_buffer[READ_BUF_SIZE];
	static size_t current_index, total_length;
	size_t copy_length;
	ssize_t read_status = 0, total_read = 0;
	char *current_ptr = NULL, *new_ptr = NULL, *newline_pos;

	current_ptr = *buffer_ptr;
	if (current_ptr && buffer_len)
		total_read = *buffer_len;
	if (current_index == total_length)
		current_index = total_length = 0;

	read_status = fetch_buffer(info, internal_buffer, &total_length);
	if (read_status == -1 || (read_status == 0 && total_length == 0))
		return (-1);

	newline_pos = find_char_in_string(internal_buffer + current_index, '\n');
	copy_length = newline_pos ? 1 + (unsigned int)(newline_pos - internal_buffer) : total_length;
	new_ptr = reallocate_memory(current_ptr, total_read, total_read ? total_read + copy_length : copy_length + 1);
	if (!new_ptr)
		return (current_ptr ? (free(current_ptr), -1) : -1);

	if (total_read)
		concatenate_strings_n(new_ptr, internal_buffer + current_index, copy_length - current_index);
	else
		copy_string_n(new_ptr, internal_buffer + current_index, copy_length - current_index + 1);

	total_read += copy_length - current_index;
	current_index = copy_length;
	current_ptr = new_ptr;

	if (buffer_len)
		*buffer_len = total_read;
	*buffer_ptr = current_ptr;
	return (total_read);
}

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl-C)
 * @signal_number: Signal number
 * Return: void
 */
void handle_sigint(__attribute__((unused))int signal_number)
{
	print_string("\n");
	print_string("$ ");
	flush_output();
}

