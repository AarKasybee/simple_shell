#include "shell.h"


/**
 * fetchcommand - get the command from the stream
 * @data: data holder
 * @n: pointer to the size of the string
 * @stream: the stream
 * Return: number of characters read | -1 (failed)
 */
int fetchcommand(data_t *data, int *n, int stream)
{
	int val;

	if (data->modo)
		_puts("$ ", 1);
	val = _getLine(data, n, stream);

	if (!data->modo && val == 0)
	{
		free(data->lineptr);
		freeSarray(data->alias, 24);
		freeSarray(data->envp, 64);
		exit(errno);
	}
	else if (val == EOF)
	{
		exit(errno);
	}
	else if (val == 1)
	{
		return 0;
	}
	else if (val == -1)
	{
		free(data->lineptr);
		freeSarray(data->alias, 24);
		freeSarray(data->envp, 64);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (checkOnlySpaces(data->lineptr))
			return val;
		else
			return 0;
	}
}


char *_which(char *cmd, data_t *data)
{
	char *path, **pathToken, *buff = NULL;
	int i, size = 0, l1 = _strlen(cmd), l2;

	path = _getenv("PATH", data);

	if (path == NULL)
		return NULL;
	pathToken = _strtok(path + 5, ":", &size);
	i = 0;
	while (i < size - 1)
	{
		l2 = _strlen(pathToken[i]);
		buff = malloc(sizeof(char) * (l1 + l2 + 2));
		if (buff == NULL)
		{
			freeSarray(pathToken, size);
			return NULL;
		}
		_memcpy(buff, pathToken[i], l2);
		buff[_strlen(pathToken[i])] = '/';
		_memcpy(buff + _strlen(pathToken[i]) + 1, cmd, l1);
		buff[l1 + l2 + 1] = '\0';
		if (access(buff, X_OK) == 0)
		{
			freeSarray(pathToken, size);
			return buff;
		}
		free(buff);
		i++;
	}
	freeSarray(pathToken, size);
	return NULL;
}


/**
 * Notfound - error when file not found
 * @data: data holder
 */
void Notfound(data_t *data)
{
	int i = 0;

	_puts(data->progName, 2);
	_puts(": ", 2);
	print_int(data->cmdCounter, 2);
	_puts(": ", 2);
	while (data->cmd[i] != NULL)
	{
		_puts(data->cmd[i], 2);
		if (data->cmd[i + 1] != NULL)
			_puts(" ", 2);
		i++;
	}
	_puts(": not found\n", 2);

	if (!data->modo)
	{
		freeData(data);
		exit(127);
	}
}

