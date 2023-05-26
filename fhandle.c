#include "shell.h"
/**
 * openFile - open a file to read from
 * @data: data holder
 * Return: file descriptor
 */
int openFile(data_t *data)
{
	int fd_src;
	int attempts = 3;

	while (attempts > 0)
	{
		fd_src = open(data->argv[1], O_RDONLY);
		if (fd_src != -1)
			return fd_src;

		attempts--;

		_puts(data->progName, 2);
		_puts(": ", 2);
		print_int(data->cmdCounter, 2);
		_puts(": Can't open ", 2);
		_puts(data->argv[1], 2);
		_puts("\n", 2);
	}

	freeData(data);
	exit(127);
}
/**
 * closeFile - close a file
 * @data: data holder
 * @fd: integer
 */
void closeFile(data_t *data, int fd)
{
	int stat;
	int attempts = 3;

	while (attempts > 0)
	{
		stat = close(fd);
		if (stat != -1)
			return;

		attempts--;

		_puts(data->progName, 2);
		_puts(": ", 2);
		print_int(data->cmdCounter, 2);
		_puts(": Can't close ", 2);
		_puts(data->argv[1], 2);
		_puts("\n", 2);
	}

	exit(EXIT_FAILURE);
}

