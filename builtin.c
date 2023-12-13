#include "shell.h"

/**
 * shell_exit - handles the exit command in the shell
 * @info: Pointer to the struct containing shell information
 * Return: Exits with a specific status, or (0) if info.argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exit_status_check;

	if (info->argv[1]) /* Check for exit argument */
	{
		exit_status_check = convert_to_int(info->argv[1]);
		if (exit_status_check == -1)
		{
			info->status = 2;
			error_message(info, "Invalid number: ");
			write_error(info->argv[1]);
			write_error_char('\n');
			return (1);
		}
		info->err_num = convert_to_int(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * shell_cd - changes the shell's current directory
 * @info: Pointer to the struct containing shell information
 * Return: Always returns 0
 */
int shell_cd(info_t *info)
{
	char *current_dir, *target_dir, cwd_buffer[1024];
	int change_dir_result;

	current_dir = getcwd(cwd_buffer, 1024);
	if (!current_dir)
		write_stdout("Error: Failed to get current working directory\n");

	if (!info->argv[1])
	{
		target_dir = fetch_env(info, "HOME=");
		change_dir_result = target_dir ? chdir(target_dir) : chdir("/");
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		target_dir = fetch_env(info, "OLDPWD=");
		if (!target_dir)
		{
			write_stdout(current_dir);
			write_stdout_char('\n');
			return (1);
		}
		write_stdout(target_dir);
		write_stdout_char('\n');
		change_dir_result = chdir(target_dir);
	}
	else
		change_dir_result = chdir(info->argv[1]);

	if (change_dir_result == -1)
	{
		error_message(info, "Unable to change directory to ");
		write_error(info->argv[1]);
		write_error_char('\n');
	}
	else
	{
		set_new_env(info, "OLDPWD", fetch_env(info, "PWD="));
		set_new_env(info, "PWD", getcwd(cwd_buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - provides help information for the shell
 * @info: Pointer to the struct containing shell information
 * Return: Always returns 0
 */
int shell_help(info_t *info)
{
	char **argument_array = info->argv;
	write_stdout("Help functionality is under development.\n");
	if (argument_array[0]) /* Placeholder for unused variable */
		write_stdout("Placeholder for future implementation.\n");
	return (0);
}

