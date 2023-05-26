#include "shell.h"

/**
 * custom_readLine - Read a line from the stream
 * @data: Data holder
 * @size: Size of the line
 * @stream: Source to read from
 * Return: Number of characters read | -1 (failed)
 */
int custom_readLine(data_t *data, int *size, int stream)
{
	int i = 0, read_count = 0, flag = 0;
	char current_char = '\0', *temp = NULL;

	if (data->lineptr == NULL)
		*size = 0;

	for (i = 0; current_char != EOF && current_char != '\n'; i++)
	{
		if (i >= *size)
		{
			*size += BUFFSIZE;
			temp = _realloc(data->lineptr, *size - BUFFSIZE, *size);
			if (temp == NULL)
			{
				free(data->lineptr), data->lineptr = NULL;
				return (-1);
			}
			data->lineptr = temp;
		}

		fflush(stdout);
		read_count = read(stream, &current_char, 1);
		read_count = custom_helper(data, read_count, i);

		if (read_count == 0)
			break;

		if (read_count == -1)
			return (-1);

		if (flag == 0 && current_char == ' ')
		{
			i--;
			continue;
		}
		else
			flag = 1;

		if (current_char == '\n')
		{
			data->lineptr[(i++)] = current_char;
			break;
		}

		data->lineptr[i] = current_char;
	}

	data->lineptr[i] = '\0';
	return (i);
}

/**
 * custom_helper - Manage the read operation
 * @data: Data holder
 * @read_count: Read status
 * @i: Character count
 * Return: 0 (empty) | -1 (failed)
 */
int custom_helper(data_t *data, int read_count, int i)
{
	if (read_count == 0)
	{
		if (i == 0)
		{
			freeData(data);
			exit(errno);
		}
		return (0);
	}

	if (read_count == -1)
	{
		free(data->lineptr), data->lineptr = NULL;
		return (-1);
	}

	return (read_count);
}

