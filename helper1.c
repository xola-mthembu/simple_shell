#include "shell.h"

/**
 *_strcmp - compare two strings
 *@first: first string to be compared
 *@second: second string to be compared
 *
 * Return: difference of the two strings
 */
int _strcmp(char *first, char *second)
{
	int i = 0;
	/* Loop through each character in the first string */
	while (first[i] != '\0')
	{
		/* If characters differ, break the loop */
		if (first[i] != second[i])
			break;
		i++;
	}
	/* Return the ASCII difference */
	return (first[i] - second[i]);
}

/**
 *_strcat - concatenates two strings
 *@destination: string to be concatenated to
 *@source:  string to concatenate
 *
 * Return: address of the new string
 */
char *_strcat(char *destination, char *source)
{
	char *new_string =  NULL;
	int len_dest = _strlen(destination);
	int len_source = _strlen(source);
	/* Allocate memory for the new string */
	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	/* Copy destination and source strings into new_string */
	_strcpy(destination, new_string);
	_strcpy(source, new_string + len_dest);
	/* Null-terminate the new string */
	new_string[len_dest + len_source] = '\0';
	return (new_string);
}

/**
 *_strspn - gets length of prefix substring
 *@str1: string to be searched
 *@str2: string to be used
 *
 * Return: number of bytes in the initial segment of str1 that are part of str2
 */
int _strspn(char *str1, char *str2)
{
	int i = 0;
	int match = 0;
	/* Loop through str1 */
	while (str1[i] != '\0')
	{
		/* If char in str1 is not in str2, break */
		if (_strchr(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}

/**
 *_strcspn - computes segment of str1 consisting of characters not in str2
 *@str1: string to be searched
 *@str2: string to be used
 *
 * Return: index at which a char in str1 exists in str2
 */
int _strcspn(char *str1, char *str2)
{
	int len = 0, i;
	/* Loop through str1 to find any char that is also in str2 */
	for (i = 0; str1[i] != '\0'; i++)
	{
		if (_strchr(str2, str1[i]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 *_strchr - locates a char in a string
 *@s: string to be searched
 *@c: char to be checked
 *
 * Return: pointer to the first occurrence of c in s
 */
char *_strchr(char *s, char c)
{
	int i = 0;
	/* Loop through the string until char is found or end of string */
	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}


