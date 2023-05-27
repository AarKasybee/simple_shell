#include "shell.h"

/**
 * _print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _print(char *string)
{
	return (write(STDOUT_FILENO, string, str_length(string)));
}
/**
 * _printer - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _printer(char *string)
{
	return (write(STDERR_FILENO, string, str_length(string)));
}

/**
 * _p_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int _p_error(int errorcode, data_of_program *data)
{
	char n_as_string[10] = {'\0'};

	long_to_string((long) data->exec_counter, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		_printer(data->program_name);
		_printer(": ");
		_printer(n_as_string);
		_printer(": ");
		_printer(data->arguments[0]);
		if (errorcode == 2)
			_printer(": Illegal number: ");
		else
			_printer(": can't cd to ");
		_printer(data->arguments[1]);
		_printer("\n");
	}
	else if (errorcode == 127)
	{
		_printer(data->program_name);
		_printer(": ");
		_printer(n_as_string);
		_printer(": ");
		_printer(data->command_name);
		_printer(": not found\n");
	}
	else if (errorcode == 126)
	{
		_printer(data->program_name);
		_printer(": ");
		_printer(n_as_string);
		_printer(": ");
		_printer(data->command_name);
		_printer(": Permission denied\n");
	}
	return (0);
}

