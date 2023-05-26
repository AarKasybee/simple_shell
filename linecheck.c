#include "shell.h"

/**
 * is_directory - Checks if the path is a directory
 * @path: Path to check
 * Return: 1 (directory) | 0 (not a directory)
 */
int is_directory(char *path)
{
	struct stat st;
	int status = stat(path, &st);

	if (status == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (1);
	}
	return (0);
}

/**
 * is_digit - Checks if the string has only digits
 * @s: String to check
 * Return: 1 (digits) | 0 (otherwise)
 */
int is_digit(char *s)
{
	int i = 0;

	for (; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * atoi_custom - Converts a string to an integer
 * @s: String to convert
 * Return: Integer value | 0 (empty string)
 */
int atoi_custom(char *s)
{
	int i = 0;
	int d0 = -1;
	unsigned int num;
	int sign = 1;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9' && d0 == -1)
		{
			d0 = i;
		}
		if (s[i] == '-' && d0 == -1)
			sign = -sign;
		i++;
	}

	if (d0 == -1)
		return (0);

	i = d0 + 1;
	num = s[d0] - '0';
	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + (s[i] - '0');
		else
			break;
		i++;
	}

	return (num * sign);
}

