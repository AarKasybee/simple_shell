#include "shell.h"

/**
 * search_builtin - search for a match in the list of built-ins.
 * @data: pointer to struct data.
 * Return: the return value of the function.
 **/
int search_builtin(data_of_program *data)
{
<<<<<<< HEAD
	int act;
	builtins options[] = {
=======
	int iterator;
	builtin_list options[] = {
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
		{"exit", b_exit},
		{"help", b_help},
		{"cd", b_cd},
		{"alias", b_alias},
		{"env", show_environment},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{NULL, NULL}
	};
<<<<<<< HEAD
	for (act = 0; options[act].builtin != NULL; act++)
	{
		if (str_compare(options[act].builtin, data->command_name, 0))
=======
	for (iterator = 0; options[iterator].name != NULL; iterator++)
	{
		if (str_compare(options[iterator].name, data->command_name, 0))
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
		{
			return (options[act].function(data));
		}
	}
	return (-1);
}
