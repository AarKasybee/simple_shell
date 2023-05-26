#include "shell.h"

/**
 * builtin - shows the environment of shell
 * @data: struct for the program
 * Return: zero if sucess
 */
int builtin(data_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;


	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{
			if (data->tokens[1][i] == '=')
			{
				var_copy = str_duplicate(get_key(cpname, data));
				if (var_copy != NULL)
					set_key(cpname, data->tokens[1] + i + 1, data);


				print_environ(data);
				if (get_key(cpname, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
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

	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * unset_env - unset env
 * @data: struct for the program's data'
 * Return: nil
 */
int unset_env(data_of_program *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	del_key(data->tokens[1], data);

	return (0);
}

