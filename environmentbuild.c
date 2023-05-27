#include "shell.h"


/**
 * show_environment - displays the environment of the shell.
 * @data: pointer to struct for the program.
 * Return: 0 if success.
 */
int show_environment(data_of_program *data)
{
	int i;
	char variable_name[50] = {'\0'};
	char *value_copy = NULL;

	if (data->arguments[1] == NULL)
		print_environment(data);
	else
	{
		for (i = 0; data->arguments[1][i]; i++)
		{
			if (data->arguments[1][i] == '=')
			{
				value_copy = str_duplicate(get_value(variable_name, data));
				if (value_copy != NULL)
					set_value(variable_name, data->arguments[1] + i + 1, data);

				print_environment(data);
				if (get_value(variable_name, data) == NULL)
				{
					_print(data->arguments[1]);
					_print("\n");
				}
				else
				{
					set_value(variable_name, value_copy, data);
					free(value_copy);
				}
				return (0);
			}
			variable_name[i] = data->arguments[1][i];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}


/**
 * set_env - set environment
 * @data: struct data
 * Return: zero if sucess
 */
int set_env(data_of_program *data)
{
	if (data->arguments[1] == NULL || data->arguments[2] == NULL)
		return (0);
	if (data->arguments[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	set_value(data->arguments[1], data->arguments[2], data);

	return (0);
}

/**
 * unset_env - unset env
 * @data: struct for the program's data'
 * Return: nil
 */
int unset_env(data_of_program *data)
{
	if (data->arguments[1] == NULL)
		return (0);
	if (data->arguments[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	del_key(data->arguments[1], data);

	return (0);
}
