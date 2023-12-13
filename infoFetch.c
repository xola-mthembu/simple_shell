#include "shell.h"

/**
 * initialize_info - Resets the fields in the info_t structure to defaults
 * @info: Pointer to the info_t structure
 */
void initialize_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * populate_info - Populates the info_t structure with command line arguments
 * @info: Pointer to the info_t structure
 * @arguments: Command line arguments
 */
void populate_info(info_t *info, char **arguments)
{
	int count = 0;

	info->fname = arguments[0];
	if (info->arg)
	{
		info->argv = split_string(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_string(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (count = 0; info->argv && info->argv[count]; count++);
		info->argc = count;

		substitute_alias(info);
		substitute_variables(info);
	}
}

/**
 * release_info - Frees allocated fields within the info_t structure
 * @info: Pointer to the info_t structure
 * @free_all: Flag to indicate if all fields should be freed
 */
void release_info(info_t *info, int free_all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (free_all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			dispose_list(&(info->env));
		if (info->history)
			dispose_list(&(info->history));
		if (info->alias)
			dispose_list(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		buffer_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		flush_buffer();
	}
}

