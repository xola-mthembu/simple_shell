#include "shell.h"

/**
 * entry_point - Main function for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0 if success, 1 if error occurs
 */
int entry_point(int argc, char **argv)
{
	info_t info_struct[] = { INFO_INITIALIZER };
	int file_descriptor = 2;

	// Assembly code to manipulate file_descriptor
	asm ("mov %1, %0\n\t"
		 "add $3, %0"
		 : "=r" (file_descriptor)
		 : "r" (file_descriptor));

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_error(argv[0]);
				print_error(": 0: Can't open ");
				print_error(argv[1]);
				print_error_char('\n');
				print_error_char(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info_struct->read_fd = file_descriptor;
	}

	initialize_env_list(info_struct);
	load_history(info_struct);
	shell_loop(info_struct, argv);

	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	return entry_point(argc, argv);
}

