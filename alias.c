#include "shell.h"
#include "shell.h"

/**
 * handle_builtin_aliases - Handle the alias command
 * @data: Data holder
 * @idx: Command index
 * Return: 1
 */
int handle_builtin_aliases(data_t *data, int idx)
{
	int i = 0, flag = 0;

	if (data->cmd[idx + 1] == NULL)
		print_aliases(data, NULL);
	else
	{
		while (data->cmd[idx + 1 + i])
		{
			if (_strchr2(data->cmd[idx + 1 + i], '='))
			{
				add_alias(data, data->cmd[idx + 1 + i]);
				flag = 1;
			}
			else
				flag = print_aliases(data, data->cmd[idx + 1 + i]);

			if (!flag)
			{
				_puts("alias: ", 2);
				_puts(data->cmd[idx + 1 + i], 2);
				_puts(" not found\n", 2);
				errno = 127;
			}
			i++;
		}
	}

	return (1);
}

/**
 * alias_handler - Handle alias substitution
 * @data: Data holder
 * @pos: Position
 * Return: Character
 */
char *alias_handler(data_t *data, int pos)
{
	int i, j, newlen, cmdlen = _strlen(data->cmd[pos]);

	for (i = 0; data->alias[i]; i++)
	{
		if (_strncmp(data->alias[i], data->cmd[pos], cmdlen) == 0
				&& data->alias[i][cmdlen] == '=')
		{
			free(data->cmd[pos]);
			newlen = _strlen(data->alias[i]) - cmdlen - 1;
			data->cmd[pos] = malloc(sizeof(char) * (newlen + 1));

			for (j = 0; j < newlen; j++)
			{
				data->cmd[pos][j] = data->alias[i][cmdlen + 1 + j];
			}
			data->cmd[pos][newlen] = '\0';
			alias_handler(data, pos);
		}
	}
	return (data->cmd[pos]);
}

/**
 * print_aliases - Print aliases
 * @data: Data holder
 * @alias: Print a specific alias, if NULL print all
 * Return: 1 (single print) | 0 (all)
 */
int print_aliases(data_t *data, char *alias)
{
	int i, j, flag = 0, qflag = 0, len;

	for (i = 0; data->alias[i] != NULL; i++)
	{
		if (alias)
		{
			if (_strncmp(data->alias[i], alias, _strlen(alias)) == 0
					&& data->alias[i][_strlen(alias)] == '=')
				flag = 1;
			else
				continue;
		}
		len = _strlen(data->alias[i]);
		for (j = 0; j < len; j++)
		{
			if (data->alias[i][j] == '=')
				qflag = 1;
			_putchar(data->alias[i][j]);
			if (qflag == 1)
			{
				_putchar('\'');
				qflag = 0;
			}
			if (j == len - 1)
			{
				_putchar('\'');
				_putchar('\n');
				break;
			}
		}
		if (flag == 1)
			return (1);
	}

	return (0);
}

/**
 * add_alias - Add an alias or overwrite an existing alias
 * @data: Data holder
 * @alia: New alias
 */
void add_alias(data_t *data, char *alia)
{
	int i, len, flag = 0, pos;

	pos = _strchr2(alia, '=');
	for (i = 0; data->alias[i] != NULL; i++)
	{
		if (_strncmp(data->alias[i], alia, pos) == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag)
		free(data->alias[i]);

	len = _strlen(alia);
	data->alias[i] = malloc(sizeof(char) * len + 3);
	if (data->alias[i] == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return;
	}

	_strcpy(data->alias[i], alia);
	data->alias[i][len] = '\0';
}

