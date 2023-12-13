#include "shell.h"

/**
 * count_list_nodes - Counts the number of nodes in a linked list
 * @head_ref: Pointer to the first node
 * Return: Number of nodes in the list
 */
size_t count_list_nodes(const list_t *head_ref)
{
	size_t node_count = 0;

	while (head_ref)
	{
		head_ref = head_ref->next;
		node_count++;
	}
	return (node_count);
}

/**
 * convert_list_to_array - Converts a linked list to an array of strings
 * @head_ref: Pointer to the first node
 * Return: Pointer to the array of strings or NULL if failed
 */
char **convert_list_to_array(list_t *head_ref)
{
	list_t *current_node = head_ref;
	size_t node_count = count_list_nodes(head_ref), idx;
	char **string_array;
	char *temp_str;

	if (!head_ref || !node_count)
		return (NULL);

	string_array = malloc(sizeof(char *) * (node_count + 1));
	if (!string_array)
		return (NULL);

	for (idx = 0; current_node; current_node = current_node->next, idx++)
	{
		temp_str = malloc(string_length(current_node->str) + 1);
		if (!temp_str)
		{
			while (idx > 0)
				free(string_array[--idx]);
			free(string_array);
			return (NULL);
		}
		copy_string(temp_str, current_node->str);
		string_array[idx] = temp_str;
	}
	string_array[idx] = NULL;
	return (string_array);
}

/**
 * display_list - Displays all elements of a list_t linked list
 * @head_ref: Pointer to the first node
 * Return: Number of nodes displayed
 */
size_t display_list(const list_t *head_ref)
{
	size_t node_count = 0;

	while (head_ref)
	{
		print_string(number_to_string(head_ref->num, 10, 0));
		print_char(':');
		print_char(' ');
		print_string(head_ref->str ? head_ref->str : "(nil)");
		print_string("\n");
		head_ref = head_ref->next;
		node_count++;
	}
	return (node_count);
}

/**
 * find_node_by_prefix - Finds the first node whose string starts with a given prefix
 * @head_ref: Pointer to the first node
 * @prefix: Prefix string to match
 * @next_char: The character following the prefix to match
 * Return: Pointer to the matching node or NULL if no match found
 */
list_t *find_node_by_prefix(list_t *head_ref, char *prefix, char next_char)
{
	char *match_ptr = NULL;

	while (head_ref)
	{
		match_ptr = check_start_with(head_ref->str, prefix);
		if (match_ptr && ((next_char == -1) || (*match_ptr == next_char)))
			return (head_ref);
		head_ref = head_ref->next;
	}
	return (NULL);
}

/**
 * find_node_index - Finds the index of a specific node in the list
 * @head_ref: Pointer to the first node
 * @node_ref: Node whose index is to be found
 * Return: Index of the node or -1 if not found
 */
ssize_t find_node_index(list_t *head_ref, list_t *node_ref)
{
	size_t index = 0;

	while (head_ref)
	{
		if (head_ref == node_ref)
			return (index);
		head_ref = head_ref->next;
		index++;
	}
	return (-1);
}

