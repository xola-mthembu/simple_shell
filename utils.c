#include "shell.h"

/**
 * parse_command - Determines the type of the command.
 * @command: Command to be parsed.
 * Return: Constant representing the type of the command.
 * Description: EXTERNAL_COMMAND (1) represents commands like /bin/ls.
 *              INTERNAL_COMMAND (2) represents commands like exit, env.
 *              PATH_COMMAND (3) represents commands found in the PATH like ls.
 *              INVALID_COMMAND (-1) represents invalid commands.
 */
int parse_command(char *command)
{
	int i;
	char *internal_command[] = {"env", "exit", NULL};
	char *path = NULL;

	/* Check if the command starts with a '/'. */
	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (EXTERNAL_COMMAND);
	}

	/* Check if the command is an internal command like 'exit' or 'env'. */
	for (i = 0; internal_command[i] != NULL; i++)
	{
		if (_strcmp(command, internal_command[i]) == 0)
			return (INTERNAL_COMMAND);
	}

	/* Check if the command is found in the PATH. */
	path = check_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}

/**
 * execute_command - Executes a command based on its type.
 * @tokenized_command: Tokenized form of the command (ls -l == {ls, -l, NULL}).
 * @command_type: Type of the command.
 * Return: void.
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);

	/* Execute if it is an external command. */
	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}

	/* Execute if the command is found in the PATH. */
	if (command_type == PATH_COMMAND)
	{
		if (execve(check_path(tokenized_command[0]), tokenized_command, NULL) == -1)
		{
			perror(_getenv("PWD"));
			exit(2);
		}
	}

	/* Execute if it is an internal command. */
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_func(tokenized_command[0]);
		func(tokenized_command);
	}

	/* Handle invalid commands. */
	if (command_type == INVALID_COMMAND)
	{
		print(shell_name, STDERR_FILENO);
		print(": 1: ", STDERR_FILENO);
		print(tokenized_command[0], STDERR_FILENO);
		print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}

/**
 * check_path - Checks if a command is found in the PATH.
 * @command: Command to be used.
 * Return: Path where the command is found in, NULL if not found.
 */
char *check_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = _getenv("PATH");
	int i;

	/* Check if PATH is NULL or empty. */
	if (path == NULL || _strlen(path) == 0)
		return (NULL);

	/* Copy the PATH and tokenize it. */
	path_cpy = malloc(sizeof(*path_cpy) * (_strlen(path) + 1));
	_strcpy(path, path_cpy);
	path_array = tokenizer(path_cpy, ":");

	/* Loop through each directory in the PATH to find the command. */
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = _strcat(path_array[i], "/");
		temp = _strcat(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}

	free(path_cpy);
	free(path_array);
	return (NULL);
}

/**
 * get_func - Retrieves a function based on the command given and a mapping.
 * @command: String to check against the mapping.
 * Return: Pointer to the proper function, or null on fail.
 */
void (*get_func(char *command))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", env}, {"exit", quit}
	};

	/* Loop through the mapping to find the corresponding function. */
	for (i = 0; i < 2; i++)
	{
		if (_strcmp(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}

	return (NULL);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @name: Name of the environment variable.
 * Return: The value of the variable as a string.
 */
char *_getenv(char *name)
{
	char **my_environ;
	char *pair_ptr;
	char *name_cpy;

	/* Loop through environment variables to find a match. */
	for (my_environ = environ; *my_environ != NULL; my_environ++)
	{
		for (pair_ptr = *my_environ, name_cpy = name;
		     *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}

		/* Return the value part if a match is found. */
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}

	return (NULL);
}



