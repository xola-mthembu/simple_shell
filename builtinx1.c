#include "shell.h"

/**
 * display_history - shows the command history list, with line numbers.
 * @info: Struct containing arguments and shell info.
 * Return: Always 0
 */
int display_history(info_t *info)
{
	show_history(info->history);
	return (0);
}

/**
 * remove_alias - removes an alias based on a given string
 * @info: Struct containing shell info
 * @alias_str: Alias string to be removed
 * Return: 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *alias_str)
{
	char *equal_sign_pos, char_backup;
	int result;

	equal_sign_pos = find_char(alias_str, '=');
	if (!equal_sign_pos)
		return (1);

	char_backup = *equal_sign_pos;
	*equal_sign_pos = 0;
	result = delete_alias(&(info->alias),
		get_alias_index(info->alias, alias_starts_with(info->alias, alias_str, -1)));
	*equal_sign_pos = char_backup;
	return (result);
}

/**
 * create_alias - creates or updates an alias
 * @info: Struct containing shell info
 * @alias_str: Alias string to be created or updated
 * Return: 0 on success, 1 on error
 */
int create_alias(info_t *info, char *alias_str)
{
	char *equal_sign_pos;

	equal_sign_pos = find_char(alias_str, '=');
	if (!equal_sign_pos)
		return (1);
	if (!*++equal_sign_pos)
		return (remove_alias(info, alias_str));

	remove_alias(info, alias_str);
	return (append_alias(&(info->alias), alias_str, 0) == NULL);
}

/**
 * output_alias - outputs a formatted alias string
 * @alias_node: Node containing the alias
 * Return: 0 on success, 1 on error
 */
int output_alias(list_t *alias_node)
{
	char *separator_pos = NULL, *current_char = NULL;

	if (alias_node)
	{
		separator_pos = find_char(alias_node->str, '=');
		for (current_char = alias_node->str; current_char <= separator_pos; current_char++)
			put_char(*current_char);
		put_char('\'');
		put_string(separator_pos + 1);
		put_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * handle_alias - handles the alias built-in command
 * @info: Struct containing shell info and arguments
 * Return: Always 0
 */
int handle_alias(info_t *info)
{
	int i = 0;
	char *equal_sign_pos = NULL;
	list_t *current_node = NULL;

	if (info->argc == 1)
	{
		current_node = info->alias;
		while (current_node)
		{
			output_alias(current_node);
			current_node = current_node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_pos = find_char(info->argv[i], '=');
		if (equal_sign_pos)
			create_alias(info, info->argv[i]);
		else
			output_alias(alias_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}

