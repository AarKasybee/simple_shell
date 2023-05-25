#include "headers.h"

/**
 * _snprintf - Concatenates directory path with command
 * @input_str: Directory path.
 * @input_str2: Command.
 * @str_buf: Buffer to store the concatenated string.
 *
 * Return: The total number of characters written to the buffer.
 */
int _snprintf(char *input_str, char *input_str2, char *str_buf)
{
	int i = 0;
	int j = 0;

	while (input_str[i] != '\0')
	{
		str_buf[i] = input_str[i];
		i++;
	}

	str_buf[i] = '/';
	i++;

	while (input_str2[j] != '\0')
	{
		str_buf[i + j] = input_str2[j];
		j++;
	}

	str_buf[i + j] = '\0';

	return (i + j);
}
