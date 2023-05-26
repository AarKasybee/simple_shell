#include "shell.h"
/**
 * builtinCheck - Check for builtin functions
 * @data: data holder
 * @cmd: command line
 * @idx: index
 * Return: integer
 */
int built(data_t *data, char *cmd, int idx)
{
	int (*fun)(data_t*, int);

	fun = get_builtin(cmd);
	if (fun)
	{
		fun(data, idx);
	}
	else
		return (0);

	return (1);
}
/**
 * get_builtin - get the corresponding built-in function to the
 * command entered.
 * @cmd: command
 * Return: function (success) | 0 (failed)
 */
int (*get_builtin(char *cmd))(data_t*, int)
{
	int i;
	builtin_t bltin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"cd", builtin_cd},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"alias", my_aliases},
		{NULL, NULL}
	};

	for (i = 0; bltin[i].name != NULL; i++)
	{
		if (_strcmp(cmd, bltin[i].name) == 0)
			return (bltin[i].f);
	}
	return (0);
}

