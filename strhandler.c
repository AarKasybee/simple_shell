#include "shell.h"

/**
 * _strcmp - Compare two strings
 * @s1: first string
 * @s2: second string
 * Return: 0 (equal) 1 (s1 greater) -1 (s2 greater)
 */
int _strcmp(char *s1, char *s2)
{
	int len = 0;

	while (s1[len] != '\0' || s2[len] != '\0')
		len++;

	for (int i = 0; i < len; i++)
	{
		if (s1[i] != s2[i])
			return s1[i] - s2[i];
	}

	return 0;
}

