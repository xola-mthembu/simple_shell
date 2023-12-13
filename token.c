#include "shell.h"

/**
 * split_string - splits a string into an array of words
 * @input: the input string
 * @delim: the delimiter string
 * Return: pointer to an array of strings or NULL on failure
 */
char **split_string(char *input, char *delim)
{
    int idx, word_idx, word_len, word_count = 0;
    char **result;

    if (!input || !(*input))
        return NULL;
    if (!delim)
        delim = " ";
    
    // Count the number of words
    for (idx = 0; input[idx] != '\0'; idx++)
        if (!is_delim(input[idx], delim) && 
            (is_delim(input[idx + 1], delim) || input[idx + 1] == '\0'))
            word_count++;

    if (word_count == 0)
        return NULL;
    
    result = malloc((word_count + 1) * sizeof(char *));
    if (!result)
        return NULL;

    for (idx = 0, word_idx = 0; word_idx < word_count; word_idx++)
    {
        while (is_delim(input[idx], delim))
            idx++;
        
        word_len = 0;
        while (!is_delim(input[idx + word_len], delim) && input[idx + word_len])
            word_len++;
        
        result[word_idx] = malloc((word_len + 1) * sizeof(char));
        if (!result[word_idx])
        {
            for (int n = 0; n < word_idx; n++)
                free(result[n]);
            free(result);
            return NULL;
        }

        for (int n = 0; n < word_len; n++)
            result[word_idx][n] = input[idx++];
        result[word_idx][word_len] = '\0';
    }
    result[word_idx] = NULL;
    return result;
}

/**
 * split_string_single_delim - splits a string into words using a single character delimiter
 * @input: the input string
 * @delim: the single character delimiter
 * Return: pointer to an array of strings or NULL on failure
 */
char **split_string_single_delim(char *input, char delim)
{
    int idx, word_idx, word_len, word_count = 0;
    char **result;

    if (!input || !(*input))
        return NULL;

    // Count the number of words
    for (idx = 0; input[idx] != '\0'; idx++)
        if (input[idx] != delim && (input[idx + 1] == delim || input[idx + 1] == '\0'))
            word_count++;

    if (word_count == 0)
        return NULL;

    result = malloc((word_count + 1) * sizeof(char *));
    if (!result)
        return NULL;

    for (idx = 0, word_idx = 0; word_idx < word_count; word_idx++)
    {
        while (input[idx] == delim)
            idx++;

        word_len = 0;
        while (input[idx + word_len] != delim && input[idx + word_len])
            word_len++;

        result[word_idx] = malloc((word_len + 1) * sizeof(char));
        if (!result[word_idx])
        {
            for (int n = 0; n < word_idx; n++)
                free(result[n]);
            free(result);
            return NULL;
        }

        for (int n = 0; n < word_len; n++)
            result[word_idx][n] = input[idx++];
        result[word_idx][word_len] = '\0';
    }
    result[word_idx] = NULL;
    return result;
}

