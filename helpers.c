#include "shell.h"

/**
 * fix_executable_path - Add the path to the executable if it exists
 * @cmd: Command
 * @data: Data holder
 * Return: Executable path or NULL
 */
char *fix_executable_path(char *cmd, data_t *data)
{
	char *exe;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		data->flag = 0;
		if (access(cmd, X_OK) == 0)
			exe = cmd;
		else
			return (NULL);
	}
	else
	{
		data->flag = 1;
		exe = find_executable(cmd, data);
	}

	return (exe);
}

/**
 * count_commands - Count the number of commands
 * @data: Data holder
 * Return: Number of commands
 */
int count_commands(data_t *data)
{
	int i, cmd_count = 1;

	for (i = 0; data->cmd[i + 1] != NULL; i++)
	{
		if (string_compare(data->cmd[i], "&&") == 0
			|| string_compare(data->cmd[i], "||") == 0
			|| string_compare(data->cmd[i], ";") == 0)
			cmd_count++;
	}

	return (cmd_count);
}

/**
 * compare_token - Compare tokens
 * @tok: Token
 * @sep: Separator
 * @flag: Flag
 * Return: Integer
 */
int compare_token(char *tok, int *sep, int *flag)
{
	if (string_compare(tok, ";") == 0)
	{
		*sep = 1;
		return (1);
	}
	else if (string_compare(tok, "&&") == 0)
	{
		*sep = 2;
		return (1);
	}
	else if (string_compare(tok, "||") == 0)
	{
		*sep = 4;
		return (1);
	}

	(void)flag;
	return (0);
}

/**
 * check_token - Token checker
 * @tok: Token
 * Return: Integer
 */
int check_token(char *tok)
{
	if (string_compare(tok, ";") == 0)
		return (1);
	else if (string_compare(tok, "&&") == 0)
		return (1);
	else if (string_compare(tok, "||") == 0)
		return (1);

	return (0);
}

