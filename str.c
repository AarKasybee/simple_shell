#include "shell.h"
/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 (equal) 1 (s1 greater) -1 (s2 greater)
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);

	return (0);
}

/**
 * _strncmp - Compare n bytes from a string
 * @s1: First string
 * @s2: Second string
 * @n: Number of bytes to compare
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
 * _strcpy - Copy a string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
	int i;
	int len = _strlen(src);

	for (i = 0; i < len; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strchr2 - Locate the first occurrence of a character in a string
 * @s: String to search in
 * @c: Character to locate
 * Return: Index (found) or 0 (not found)
 */
int _strchr2(const char *s, int c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
			return (i);
	}
	if (s[i] == c)
		return (i);
	return (0);
}

/**
 * _strcat - Concatenate two strings
 * @dest: Destination string
 * @src: Source string
 * Return: Pointer to the destination string
 */
char *_strcat(char *dest, const char *src)
{
	int i = 0;
	int len = _strlen(dest);

	while (src[i] != '\0')
	{
		dest[len + i] = src[i];
		i++;
	}
	dest[len + i] = '\0';
	return (dest);
}

