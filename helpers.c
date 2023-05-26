#include "shell.h"
/**
 * exeFixer - add the path to the exe if it exists
 * @cmd: command
 * @data: data holder
 * Return: character
 */
char *exeFixer(char *cmd, data_t *data)
{
	char *exe = NULL;
	int attempts = 3;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		data->flag = 0;
		if (access(cmd, X_OK) == 0)
			exe = cmd;
		else
			return NULL;
	}
	else
	{
		data->flag = 1;
		while (attempts > 0)
		{
			exe = _which(cmd, data);
			if (exe != NULL)
				return exe;

			attempts--;
		}
	}

	return exe;
}

/**
 * commandsCounter - count the numer of commands
 * @data: data holder
 * Return: number of commands
 */
int commandsCounter(data_t *data)
{
	int i, cmdCount = 1;

	for (i = 0; data->cmd[i + 1] != NULL; i++)
	{
		if (_strcmp(data->cmd[i], "&&") == 0
				|| _strcmp(data->cmd[i], "||") == 0
				|| _strcmp(data->cmd[i], ";") == 0)
			cmdCount++;
	}
	return (cmdCount);
}
/**
 * tokCompare - Compare tokens
 * @tok: token
 * @sep: separator
 * @flag: flag
 * Return: int
 */
int tokCompare(char *tok, int *sep, int *flag)
{
	if (_strcmp(tok, ";") == 0)
	{
		*sep = 1;
		return 1;
	}

	if (_strcmp(tok, "&&") == 0)
	{
		*sep = 2;
		return 1;
	}

	if (_strcmp(tok, "||") == 0)
	{
		*sep = 4;
		return 1;
	}

	(void)flag;
	return 0;
}
/**
 * tokChecker - token checker
 * @tok: token
 * Return: int
 */
int tokChecker(char *tok)
{
	if (_strcmp(tok, ";") == 0)
		return 1;

	if (_strcmp(tok, "&&") == 0)
		return 1;

	if (_strcmp(tok, "||") == 0)
		return 1;

	return 0;
}

