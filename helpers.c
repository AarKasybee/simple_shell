#include "headers.h"
#include <stdio.h>
#include <string.h>

/**
 * _strcat - a function that concatenates two strings.
 * @dest: an input string
 * @src: an input string
 * Return: A pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
	char *temp = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (temp);
}

/**
 * _strcmp - Compare two strings
 * @s1: string
 * @s2: string
 * Return: negative int if s1 < s2, 0 if matching, and positive int if s1 > s2
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * *_strcpy - copies the string pointed to by src
 * including the terminating null byte (\0)
 * to the buffer pointed to by dest
 * @dest: pointer to the buffer in which we copy the string
 * @src: string to be copied
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int len, i;

	len = 0;
	while (src[len] != '\0')
	{
		len++;
	}

	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

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
	extern char **environ;
	
	int i;
	/* Iterate through each environment variable */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Split the variable into name and value */
		char *variable = environ[i];
		char *equal_sign = _strchr(variable, '=');
		size_t  name_length;
		if (equal_sign == NULL)
			continue;

		/* Compare the variable name with the provided name */
		name_length = equal_sign - variable;
		if (strncmp(variable, name, name_length) == 0)
		{
			/* Return the value part of the variable */
			return equal_sign + 1;
		}
	}

	/* Variable not found */
	return NULL;
}

