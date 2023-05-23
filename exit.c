#include "headers.h"

/**
 * exit_func - This function exits the terminal of the shell
 * @command: user inputs command
 *
 * Return: nothing
 */
void exit_func(char **command)
{
	if (_strcmp(command[0], "exit") == 0) /* handle exit command */
	{
		exit(0);
	}
}

