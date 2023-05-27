#include "shell.h"

/**
 * search_builtin - search for a match in the list of built-ins.
 * @data: pointer to struct data.
 * Return: the return value of the function.
 **/
int search_builtin(data_of_program *data)
{
	int iterator;
	builtin_list options[] = {
		{"exit", b_exit},
		{"help", b_help},
		{"cd", b_cd},
		{"alias", b_alias},
		{"env", show_environment},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};
	for (iterator = 0; options[iterator].name != NULL; iterator++)
	{
		if (str_compare(options[iterator].name, data->command_name, 0))
		{
			return (options[iterator].function(data));
		}
	}
	return (-1);
}
