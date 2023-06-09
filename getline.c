#include "shell.h"

/**
 * read_line - read one line from the prompt.
 * @data: pointer to struct for the program's data.
 *
 * Return: the number of bytes read.
 */
int read_line(data_of_program *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *command_array[10] = {NULL};
	static char operator_array[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!command_array[0] || (operator_array[0] == '&' && errno != 0) ||
	    (operator_array[0] == '|' && errno == 0))
	{
		for (i = 0; command_array[i]; i++)
		{
			free(command_array[i]);
			command_array[i] = NULL;
		}

		bytes_read = read(data->file_descriptor, &buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			command_array[i] = str_duplicate(_strtok(i ? NULL : buffer, "\n;"));
			i = process_logic_op(command_array, i, operator_array);
		} while (command_array[i++]);
	}

	data->input_line = command_array[0];
	for (i = 0; command_array[i]; i++)
	{
		command_array[i] = command_array[i + 1];
		operator_array[i] = operator_array[i + 1];
	}

	return (str_length(data->input_line));
}


/**
 * process_logic_op - checks and splits for && and || operators.
 * @command_array: array of commands.
 * @index: index in the command_array to be checked.
 * @operator_array: array of logical operators for each previous command.
 *
 * Return: index of the last command in the command_array.
 */
int process_logic_op(char *command_array[], int index, char operator_array[])
{
	char *temp = NULL;
	int j;

	for (j = 0; command_array[index] != NULL && command_array[index][j]; j++)
	{
		if (command_array[index][j] == '&' && command_array[index][j + 1] == '&')
		{
			temp = command_array[index];
			command_array[index][j] = '\0';
			command_array[index] = str_duplicate(command_array[index]);
			command_array[index + 1] = str_duplicate(temp + j + 2);
			index++;
			operator_array[index] = '&';
			free(temp);
			j = 0;
		}
		if (command_array[index][j] == '|' && command_array[index][j + 1] == '|')
		{
			temp = command_array[index];
			command_array[index][j] = '\0';
			command_array[index] = str_duplicate(command_array[index]);
			command_array[index + 1] = str_duplicate(temp + j + 2);
			index++;
			operator_array[index] = '|';
			free(temp);
			j = 0;
		}
	}
	return (index);
}

