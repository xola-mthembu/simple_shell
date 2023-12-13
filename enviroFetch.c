#include "shell.h"

/**
 * acquire_environ - Retrieves a copy of the environment as a string array
 * @info: Structure containing shell-related information
 * Return: Pointer to the string array of environment variables
 */
char **acquire_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = convert_list_to_string_array(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * remove_env_variable - Removes a specified environment variable
 * @info: Structure containing shell information and potential arguments
 * @variable: The name of the environment variable to be removed
 * Return: 1 if the variable was removed, 0 otherwise
 */
int remove_env_variable(info_t *info, char *variable)
{
	list_t *current_node = info->env;
	size_t node_index = 0;
	char *match;

	if (!current_node || !variable)
		return (0);

	while (current_node)
	{
		match = match_prefix(current_node->str, variable);
		if (match && *match == '=')
		{
			info->env_changed = erase_node_at_index(&(info->env), node_index);
			node_index = 0;
			current_node = info->env;
			continue;
		}
		current_node = current_node->next;
		node_index++;
	}
	return (info->env_changed);
}

/**
 * create_or_modify_env - Initializes or modifies an environment variable
 * @info: Structure containing shell information
 * @variable: The environment variable name
 * @value: The value to set for the environment variable
 * Return: 0 on success, 1 on failure
 */
int create_or_modify_env(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *current_node;
	char *match;

	if (!variable || !value)
		return (0);

	buffer = malloc(string_length(variable) + string_length(value) + 2);
	if (!buffer)
		return (1);
	copy_string(buffer, variable);
	append_string(buffer, "=");
	append_string(buffer, value);
	current_node = info->env;
	while (current_node)
	{
		match = match_prefix(current_node->str, variable);
		if (match && *match == '=')
		{
			free(current_node->str);
			current_node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		current_node = current_node->next;
	}
	append_node(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

