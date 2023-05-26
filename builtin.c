#include "shell.h"

/**
 * check_builtin - Check if the command is a built-in function
 * @data: Data holder
 * @cmd: Command line
 * @idx: Index
 * Return: 1 if the command is a built-in function, 0 otherwise
 */
int check_builtin(data_t *data, char *cmd, int idx)
{
	int (*fun)(data_t *, int);

	fun = get_builtin_function(cmd);
	if (fun)
	{
		fun(data, idx);
		return (1);
	}
	else
		return (0);
}

/**
 * get_builtin_function - Get the corresponding built-in function for the command
 * @cmd: Command
 * Return: Pointer to the built-in function if found, NULL otherwise
 */
int (*get_builtin_function(char *cmd))(data_t *, int)
{
	int i;
	builtin_t builtin_functions[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"cd", builtin_cd},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"alias", builtin_aliases},
		{NULL, NULL}
	};

	for (i = 0; builtin_functions[i].name != NULL; i++)
	{
		if (_strcmp(cmd, builtin_functions[i].name) == 0)
			return (builtin_functions[i].function);
	}

	return (NULL);
}

