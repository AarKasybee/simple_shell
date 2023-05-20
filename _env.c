#include "headers.h"

/**
 * env_func - built-in, that prints the current environment
 * @command: command input fromt the user
 *
 * Return: nothing
 */
void env_func(char **command)
{
	if (_strcmp(command[0], "env") == 0) /* handle env command */
	{
		char **env = environ;

		while (*env)
		{
			_puts("\n");
		}
		return;
	}
}
