#include "headers.h"

/**
 * _snprintf - Should work like snprintf but without formatting
 * @input_str: First input string.
 * @input_str2: Second input string.
 * @str_buf: Buffer to store the concatenated string.
 *
 * Return: The total number of characters written to the buffer.
 */
int _snprintf(char *input_str, char *input_str2, char *str_buf)
{
	int buf_len = _strlen(input_str) + _strlen(input_str2);
	int i = 0;
	int j = 0;

	str_buf = (char *)malloc((buf_len + 2) * sizeof(char));
	if (str_buf == NULL)
	{
		return (-1);
	}

	while (input_str[i] != '\0')
	{
		str_buf[i] = input_str[i];
		i++;
	}

	str_buf[i] = '/';

	while (input_str2[j] != '\0')
	{
		str_buf[i + j + 1] = input_str2[j];
		j++;
	}

	str_buf[i + j + 1] = '\0';
	return (i + j + 1);
}
