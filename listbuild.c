#include "shell.h"

/**
 * b_list - search for match
 * @data: struct data
 * Return: Returns the return of the function
 **/
int b_list(data_of_program *data)
{
	int act;
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
	for (act = 0; options[act].builtin != NULL; act++)
	{
		if (str_compare(options[act].builtin, data->command_name, 0))
		{
			return (options[act].function(data));
		}
	}
	return (-1);
}

