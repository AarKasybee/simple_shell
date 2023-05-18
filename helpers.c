#include "headers.h"

/**
 * _strlen -  a function that returns the length of a string.
 * @s: An input string
 * Return: Nothing
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}

/**
 * *_strdup - copies the input string
 * @string: input string
 *
 * Return: *ptr to the copied string or  NULL (if Error)
 */
char *_strdup(char *string)
{
	char *dup;
	unsigned int i = 0, length = 0;

	if (string == NULL)
		return (NULL);

	while (string[length])
		length++;

	dup = malloc(sizeof(char) * (length + 1));

	if (dup == NULL)
		return (NULL);

	while ((dup[i] = string[i]) != '\0')
		i++;

	return (dup);
}

/**
 * _strchr - a function that locates character in a string
 * @s: input string
 * @c: input character
 * Return: return pointer to c character
 */

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (c == *s)
			return (s);
		s++;
	}
	if (c == *s)
		return (s);
	return (NULL);
}


/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i;

	/* Iterate through each environment variable */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Split the variable into name and value */
		char *variable = environ[i];
		char *equal_sign = _strchr(variable, '=');
		size_t  name_length;

		if (equal_sign == NULL)
		{
			continue;
		}

		/* Compare the variable name with the provided name */
		name_length = equal_sign - variable;
		if (_strncmp(variable, name, name_length) == 0)
		{
			/* Return the value part of the variable */
			return (equal_sign + 1);
		}
	}

	/* Variable not found */
	return (NULL);
}

/**
 * _strncmp - Compare two strings up to a specified number of characters
 * @str1: Pointer to the first string
 * @str2: Pointer to the second string
 * @n: Maximum number of characters to compare
 *
 * Return: An integer less than, equal to, or greater than zero if the first
 * n bytes of str1 are found to be less than, equal to, or greater than the
 * first n bytes of str2, respectively.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		else if (str1[i] == '\0')
			return (-1);
		else if (str2[i] == '\0')
			return (1);

		if (str1[i] != str2[i])
			return ((int)(unsigned char)str1[i] - (int)(unsigned char)str2[i]);
	}

	return (0);
}

