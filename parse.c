#include "shell.h"

/**
 * check_executable - checks if a given path points to an executable file
 * @info: Pointer to the info struct
 * @file_path: Path of the file to check
 * Return: 1 if executable, 0 otherwise
 */
int check_executable(info_t *info, char *file_path)
{
	struct stat file_stat;

	if (!file_path || stat(file_path, &file_stat))
		return (0);

	return (file_stat.st_mode & S_IFREG) ? 1 : 0;
}

/**
 * copy_segment - copies a segment of a string into a buffer
 * @source_str: Source string to copy from
 * @begin: Starting index of the segment
 * @end: Ending index of the segment
 * Return: Pointer to the buffer with copied segment
 */
char *copy_segment(char *source_str, int begin, int end)
{
	static char segment_buf[1024];
	int idx = 0;

	for (; begin < end; begin++)
		if (source_str[begin] != ':')
			segment_buf[idx++] = source_str[begin];
	segment_buf[idx] = '\0';

	return segment_buf;
}

/**
 * locate_command - locates a command in the provided PATH string
 * @info: Pointer to the info struct
 * @path_str: PATH environment variable string
 * @command: Command to search for in PATH
 * Return: Full path to the command if found, NULL otherwise
 */
char *locate_command(info_t *info, char *path_str, char *command)
{
	int idx = 0, path_start = 0;
	char *resolved_path;

	if (!path_str)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
		if (check_executable(info, command))
			return (command);

	while (1)
	{
		if (!path_str[idx] || path_str[idx] == ':')
		{
			resolved_path = copy_segment(path_str, path_start, idx);
			if (!*resolved_path)
				_strcat(resolved_path, command);
			else
			{
				_strcat(resolved_path, "/");
				_strcat(resolved_path, command);
			}
			if (check_executable(info, resolved_path))
				return (resolved_path);

			if (!path_str[idx])
				break;
			path_start = idx;
		}
		idx++;
	}
	return (NULL);
}

