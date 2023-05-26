#include "shell.h"

/**
 * _strcmp - Compare two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 (equal) 1 (s1 greater) -1 (s2 greater)
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++)
	{

	}

	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);

	return (0);
}


/**
 * _strncmp - Compare n bytes from a string
 * @s1: first string
 * @s2: second string
 * @n: n bytes
 * Return: 0 (equal) 1 (s1 greater) -1 (s2 greater)
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
		{
			return (s1[i] - s2[i]);
		}
	}

	return (0);
}

/**
 * _strcpy - print every other character of a string
 *@src: pointer to a string to copy
 *@dest: pointer destination
 *Return: return dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;
	int l = _strlen(src);

	while (i < l)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}



/**
 * _strchr2 - check if a character is in a string
 * @s: string
 * @c: character to locate first appearance
 * Return: index (found) | 0 (not found)
 */

int _strchr2(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	return (0);
}

/**
 * _strcat - Concatenate two strings
 * @dest: destinatin string
 * @src: source string
 * Return: pointer to string @dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int len = 0;

	while (dest[len] != '\0')
		len++;

	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}

