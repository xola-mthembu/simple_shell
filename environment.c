#include "shell.h"

/**
 * display_env - Outputs the current environment
 * @info: Structure with shell information and potential arguments
 * Return: Always returns 0
 */
int display_env(info_t *info)
{
	output_env_list(info->env);
	return (0);
}

/**
 * fetch_env_value - Retrieves the value of an environment variable
 * @info: Structure with shell information
 * @var_name: Name of the environment variable
 * Return: Pointer to the value of the environment variable
 */
char *fetch_env_value(info_t *info, const char *var_name)
{
	list_t *current_node = info->env;
	char *value_pointer;

	while (current_node)
	{
		value_pointer = match_start(current_node->str, var_name);
		if (value_pointer && *value_pointer)
			return (value_pointer);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * initialize_env_var - Initializes or modifies an environment variable
 * @info: Structure with shell information
 * Return: 0 on success, 1 on failure
 */
int initialize_env_var(info_t *info)
{
	if (info->argc != 3)
	{
		write_to_stderr("Error: Incorrect number of arguments\n");
		return (1);
	}
	if (set_env_var(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * remove_env_var - Removes an environment variable
 * @info: Structure with shell information
 * Return: Always returns 0
 */
int remove_env_var(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		write_to_stderr("Error: Too few arguments.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		unset_env_var(info, info->argv[index]);

	return (0);
}

/**
 * fill_env_list - Fills the environment variables list
 * @info: Structure with shell information
 * Return: Always returns 0
 */
int fill_env_list(info_t *info)
{
	list_t *new_node = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		append_node_to_end(&new_node, environ[index], 0);
	info->env = new_node;
	return (0);
}

