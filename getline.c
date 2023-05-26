#include "shell.h"
int _getLine(data_t *data, int *size, int stream)
{
	int i = 0, rd = 0, flag = 0;
	char ch = '\0', *tmp = NULL;

	if (data->lineptr == NULL)
		*size = 0;

	while (ch != EOF && ch != '\n')
	{
		if (i >= *size)
		{
			*size += BUFFSIZE;
			tmp = _realloc(data->lineptr, *size - BUFFSIZE, *size);
			if (tmp == NULL)
			{
				free(data->lineptr);
				data->lineptr = NULL;
				return (-1);
			}
			data->lineptr = tmp;
		}

		fflush(stdout);
		rd = read(stream, &ch, 1);
		rd = lineHelper(data, rd, i);

		if (rd == 0)
			break;
		if (rd == -1)
			return (-1);

		if (flag == 0 && ch == ' ')
		{
			i--;
		}
		else
		{
			flag = 1;

			if (ch == '\n')
				break;

			data->lineptr[i] = ch;
		}

		i++;
	}

	data->lineptr[i] = '\0';
	return i;
}

int lineHelper(data_t *data, int rd, int i)
{
	if (rd == 0)
	{
		if (i == 0)
		{
			freeData(data);
			exit(errno);
		}
		return 0;
	}
	else if (rd == -1)
	{
		free(data->lineptr);
		data->lineptr = NULL;
		return -1;
	}
	else
	{
		return rd;
	}
}

