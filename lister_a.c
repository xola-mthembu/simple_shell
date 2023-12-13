#include "shell.h"

/**
 * insert_node_front - Inserts a new node at the beginning of a linked list
 * @head_ref: Reference to the head of the list
 * @data: String data for the new node
 * @index: Index number for the node, typically used for history tracking
 * Return: Pointer to the newly added node
 */
list_t *insert_node_front(list_t **head_ref, const char *data, int index)
{
	list_t *new_node;

	if (!head_ref)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	fill_memory((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;
	if (data)
	{
		new_node->str = duplicate_string(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = *head_ref;
	*head_ref = new_node;

	return (new_node);
}

/**
 * append_node - Appends a new node to the end of a linked list
 * @head_ref: Reference to the head of the list
 * @data: String data for the new node
 * @index: Index number for the node
 * Return: Pointer to the newly added node
 */
list_t *append_node(list_t **head_ref, const char *data, int index)
{
	list_t *new_node, *last;

	if (!head_ref)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	fill_memory((void *)new_node, 0, sizeof(list_t));
	new_node->num = index;
	if (data)
	{
		new_node->str = duplicate_string(data);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->next = NULL;

	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return (new_node);
	}

	last = *head_ref;
	while (last->next)
		last = last->next;
	last->next = new_node;

	return (new_node);
}

/**
 * display_list_string - Displays the string elements of a list_t list
 * @head: Pointer to the first node of the list
 * Return: Number of nodes in the list
 */
size_t display_list_string(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		print_string(head->str ? head->str : "(nil)");
		print_string("\n");
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * remove_node_by_index - Removes a node at a specific index
 * @head_ref: Reference to the head of the list
 * @index: Index of the node to be removed
 * Return: 1 if successful, 0 if unsuccessful
 */
int remove_node_by_index(list_t **head_ref, unsigned int index)
{
	list_t *temp, *prev;
	unsigned int count = 0;

	if (!head_ref || !*head_ref)
		return (0);

	temp = *head_ref;
	if (index == 0)
	{
		*head_ref = temp->next;
		free(temp->str);
		free(temp);
		return (1);
	}

	for (count = 0; temp != NULL && count < index; count++)
	{
		prev = temp;
		temp = temp->next;
	}
	if (!temp)
		return (0);

	prev->next = temp->next;
	free(temp->str);
	free(temp);
	return (1);
}

/**
 * dispose_all_nodes - Frees all nodes of a linked list
 * @head_ref: Reference to the head of the list
 */
void dispose_all_nodes(list_t **head_ref)
{
	list_t *current, *next_node;

	if (!head_ref || !*head_ref)
		return;

	current = *head_ref;
	while (current)
	{
		next_node = current->next;
		free(current->str);
		free(current);
		current = next_node;
	}
	*head_ref = NULL;
}

