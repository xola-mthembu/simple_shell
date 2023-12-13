#include "shell.h"

/**
 * fetch_history_path - Retrieves the path to the history file
 * @info: Struct containing shell info and parameters
 * Return: Allocated string containing the history file path
 */
char *fetch_history_path(info_t *info)
{
	char *buffer, *home_dir;

	home_dir = fetch_env(info, "HOME=");
	if (!home_dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_len(home_dir) + string_len(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	copy_string(buffer, home_dir);
	append_string(buffer, "/");
	append_string(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * save_history - Saves the shell history to a file
 * @info: Struct containing shell info and parameters
 * Return: 1 on success, -1 on failure
 */
int save_history(info_t *info)
{
	ssize_t file_descriptor;
	char *history_file = fetch_history_path(info);
	list_t *current_node = NULL;

	if (!history_file)
		return (-1);

	file_descriptor = open(history_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(history_file);
	if (file_descriptor == -1)
		return (-1);
	for (current_node = info->history; current_node; current_node = current_node->next)
	{
		write_to_fd(current_node->str, file_descriptor);
		write_char_to_fd('\n', file_descriptor);
	}
	write_char_to_fd(BUFFER_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * load_history - Reads the shell history from a file
 * @info: Struct containing shell info and parameters
 * Return: History count on success, 0 on failure
 */
int load_history(info_t *info)
{
	int index, last_position = 0, line_counter = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat stat_buf;
	char *buffer = NULL, *history_file = fetch_history_path(info);

	if (!history_file)
		return (0);

	file_descriptor = open(history_file, O_RDONLY);
	free(history_file);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &stat_buf))
		file_size = stat_buf.st_size;
	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = '\0';
	if (read_length <= 0)
		return (free(buffer), 0);

	close(file_descriptor);
	for (index = 0; index < file_size; index++)
	{
		if (buffer[index] == '\n')
		{
			buffer[index] = '\0';
			append_to_history_list(info, buffer + last_position, line_counter++);
			last_position = index + 1;
		}
	}
	if (last_position != index)
		append_to_history_list(info, buffer + last_position, line_counter++);

	free(buffer);
	info->histcount = line_counter;
	while (info->histcount-- >= MAX_HISTORY)
		remove_node_at_index(&(info->history), 0);

	update_history_numbers(info);
	return (info->histcount);
}

/**
 * append_to_history_list - Adds a new entry to the history list
 * @info: Struct containing shell info and parameters
 * @buffer: The history line to add
 * @line_counter: The current line number in the history
 * Return: Always 0
 */
int append_to_history_list(info_t *info, char *buffer, int line_counter)
{
	list_t *new_node = NULL;

	if (info->history)
		new_node = info->history;
	add_node_to_end(&new_node, buffer, line_counter);

	if (!info->history)
		info->history = new_node;
	return (0);
}

/**
 * update_history_numbers - Renumber the history list after modifications
 * @info: Struct containing shell info and parameters
 * Return: The updated history count
 */
int update_history_numbers(info_t *info)
{
	list_t *current_node = info->history;
	int counter = 0;

	while (current_node)
	{
		current_node->num = counter++;
		current_node = current_node->next;
	}
	return (info->histcount = counter);
}

