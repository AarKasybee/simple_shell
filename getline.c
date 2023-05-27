#include "shell.h"

/**
<<<<<<< HEAD
 * _getline - read one line from prompt
 * @data: struct for the program's data
=======
 * read_line - read one line from the prompt.
 * @data: pointer to struct for the program's data.
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
 *
 * Return: the number of bytes read.
 */
int read_line(data_of_program *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *command_array[10] = {NULL};
	static char operator_array[10] = {'\0'};
	ssize_t bytes_read, i = 0;

<<<<<<< HEAD
	if (!array_commands[0] || (array_operators[0] == '&' && errno != 0) ||
			(array_operators[0] == '|' && errno == 0))
=======
	if (!command_array[0] || (operator_array[0] == '&' && errno != 0) ||
	    (operator_array[0] == '|' && errno == 0))
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
	{
		for (i = 0; command_array[i]; i++)
		{
			free(command_array[i]);
			command_array[i] = NULL;
		}

<<<<<<< HEAD
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
=======
		bytes_read = read(data->file_descriptor, &buffer, BUFFER_SIZE - 1);
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			command_array[i] = str_duplicate(_strtok(i ? NULL : buffer, "\n;"));
			i = process_logic_op(command_array, i, operator_array);
		} while (command_array[i++]);
	}

<<<<<<< HEAD
	data->input_line = array_commands[0];
	for (i = 0; array_commands[i]; i++)
=======
	data->input_line = command_array[0];
	for (i = 0; command_array[i]; i++)
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
	{
		command_array[i] = command_array[i + 1];
		operator_array[i] = operator_array[i + 1];
	}

	return (str_length(data->input_line));
}


/**
<<<<<<< HEAD
 * logic_op - checks for && and || operators
 * @array_commands: array of the commands.
 * @i: index in the array_commands to be checked
 * @array_operators: array of the logical operators for each previous command
 * Return: index of the last command in the array_commands.
=======
 * process_logic_op - checks and splits for && and || operators.
 * @command_array: array of commands.
 * @index: index in the command_array to be checked.
 * @operator_array: array of logical operators for each previous command.
 *
 * Return: index of the last command in the command_array.
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
 */
int process_logic_op(char *command_array[], int index, char operator_array[])
{
	char *temp = NULL;
	int j;

<<<<<<< HEAD
	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
=======
	for (j = 0; command_array[index] != NULL && command_array[index][j]; j++)
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
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

