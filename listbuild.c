#include "shell.h"

/**
 * b_list - search for match
 * @data: struct data
 * Return: Returns the return of the function
 **/
int b_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", b_exit},
		{"help", b_help},
		{"cd", b_cd},
		{"alias", b_alias},
		{"env", builtin},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
			return (options[iterator].function(data));
		}
	}
	return (-1);
}

