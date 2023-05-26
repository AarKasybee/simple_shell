#include "shell.h"
/**
 * prompt - Get the command from the stream
 * @data: Data holder
 * @n: Pointer to the size of the string
 * @stream: The stream
 * Return: Number of characters read | -1 (failed)
 */
int prompt(data_t *data, int *n, int stream)
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
	if (val == EOF)
	{
		exit(errno);
	}
	if (val == 1)
		return (0);

	if (val == -1)
	{
		free(data->lineptr);
		freeSarray(data->alias, 24);
		freeSarray(data->envp, 64);
		exit(EXIT_FAILURE);
	}
	if (checkOnlySpaces(data->lineptr))
		return (val);
	return (0);
}

/**
 * _which - Find the path of a filename
 * @cmd: Filename to find its path
 * @data: Data holder
 * Return: The file's path | NULL (not found)
 */
char *_which(char *cmd, data_t *data)
{
	char *path, **pathToken, *buff = NULL;
	int i, size = 0, l1 = _strlen(cmd), l2;

	path = _getenv("PATH", data);

	if (path == NULL)
		return (NULL);
	pathToken = _strtok(path + 5, ":", &size);
	for (i = 0; i < size - 1; i++)
	{
		l2 = _strlen(pathToken[i]);
		buff = malloc(sizeof(char) * (l1 + l2 + 2));
		if (buff == NULL)
		{
			freeSarray(pathToken, size);
			return (NULL);
		}
		_memcpy(buff, pathToken[i], l2);
		buff[_strlen(pathToken[i])] = '/';
		_memcpy(buff + _strlen(pathToken[i]) + 1, cmd, l1);
		buff[l1 + l2 + 1] = '\0';
		if (access(buff, X_OK) == 0)
		{
			freeSarray(pathToken, size);
			return (buff);
		}
		free(buff);
	}
	freeSarray(pathToken, size);
	return (NULL);
}

/**
 * Notfound - Error when file not found
 * @data: Data holder
 */
void Notfound(data_t *data)
{
	_puts(data->progName, 2);
	_puts(": ", 2);
	print_int(data->cmdCounter, 2);
	_puts(": ", 2);
	_puts(data->cmd[0], 2);
	_puts(": not found\n", 2);

	if (!data->modo)
	{
		freeData(data);
		exit(127);
	}
}

