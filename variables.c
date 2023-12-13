#include "shell.h"

/**
 * identify_chain_type - identifies if current character in buffer is a command chain delimiter
 * @param_info: parameter struct
 * @buffer: character buffer
 * @position: current position in buffer
 * Return: 1 if delimiter found, 0 otherwise
 */
int identify_chain_type(info_t *param_info, char *buffer, size_t *position)
{
    size_t index = *position;

    if (buffer[index] == '|' && buffer[index + 1] == '|')
    {
        buffer[index] = '\0';
        index++;
        param_info->cmd_buf_type = CMD_OR;
    }
    else if (buffer[index] == '&' && buffer[index + 1] == '&')
    {
        buffer[index] = '\0';
        index++;
        param_info->cmd_buf_type = CMD_AND;
    }
    else if (buffer[index] == ';')
    {
        buffer[index] = '\0';
        param_info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return 0;
    }
    *position = index;
    return 1;
}

/**
 * evaluate_chain_continuation - decides whether to continue based on last command status
 * @param_info: parameter struct
 * @buffer: character buffer
 * @position: current position in buffer
 * @start: start position in buffer
 * @length: total length of buffer
 */
void evaluate_chain_continuation(info_t *param_info, char *buffer, size_t *position, size_t start, size_t length)
{
    size_t index = *position;

    if ((param_info->cmd_buf_type == CMD_AND && param_info->status != 0) ||
        (param_info->cmd_buf_type == CMD_OR && param_info->status == 0))
    {
        buffer[start] = '\0';
        index = length;
    }
    *position = index;
}

/**
 * substitute_alias - substitutes aliases in the token array
 * @param_info: parameter struct
 * Return: 1 if substitution made, 0 otherwise
 */
int substitute_alias(info_t *param_info)
{
    for (int i = 0; i < 10; i++)
    {
        list_t *alias_node = node_starts_with(param_info->alias, param_info->argv[0], '=');
        if (!alias_node)
            return 0;

        char *alias_value = _strchr(alias_node->str, '=');
        if (!alias_value)
            return 0;
        alias_value = _strdup(alias_value + 1);

        free(param_info->argv[0]);
        param_info->argv[0] = alias_value;
    }
    return 1;
}

/**
 * substitute_variables - replaces variables in the token array
 * @param_info: parameter struct
 * Return: 1 if substitution made, 0 otherwise
 */
int substitute_variables(info_t *param_info)
{
    for (int i = 0; param_info->argv[i]; i++)
    {
        if (param_info->argv[i][0] != '$' || !param_info->argv[i][1])
            continue;

        char *replacement = NULL;
        if (!_strcmp(param_info->argv[i], "$?"))
            replacement = _strdup(convert_number(param_info->status, 10, 0));
        else if (!_strcmp(param_info->argv[i], "$$"))
            replacement = _strdup(convert_number(getpid(), 10, 0));
        else
        {
            list_t *env_node = node_starts_with(param_info->env, &param_info->argv[i][1], '=');
            if (env_node)
                replacement = _strdup(_strchr(env_node->str, '=') + 1);
            else
                replacement = _strdup("");
        }

        if (replacement)
        {
            free(param_info->argv[i]);
            param_info->argv[i] = replacement;
        }
    }
    return 1;
}

/**
 * substitute_string - substitutes a string with a new one
 * @old_str: address of the old string
 * @new_str: new string to replace
 * Return: 1 on substitution, 0 otherwise
 */
int substitute_string(char **old_str, char *new_str)
{
    if (old_str && *old_str)
    {
        free(*old_str);
        *old_str = new_str;
        return 1;
    }
    return 0;
}

