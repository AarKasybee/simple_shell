#include "shell.h"
/**
 * my_aliases - handle the alias command
 * @data: data holder
 * @idx: command index
 * Return: 1
 */
int my_aliases(data_t *data, int idx)
{
	int i = 0, flag = 0;

	if (data->cmd[idx + 1] == NULL)
		printAliases(data, NULL);
	else
	{
		while (data->cmd[idx + 1 + i])
		{
			char *cmd = data->cmd[idx + 1 + i];
			switch (cmd[0])
			{
				case '=':
					addAlias(data, cmd);
					flag = 1;
					break;
				default:
					flag = printAliases(data, cmd);
					break;
			}

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
 * aliasHandler - Handle alias
 * @data: data holder
 * @pos: pos
 * Return: Character
 */
char *aliasHandler(data_t *data, int pos)
{
	int i = 0, j, newlen, cmdlen = _strlen(data->cmd[pos]);

	while (data->alias[i])
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
			pos = 0; /* Resetting position to check if there are more alias expansions*/
			i = 0; /*Resetting index to start from the beginning of the alias array*/
		}
		else
		{
			i++;
		}
	}
	return (data->cmd[pos]);
}
/**
 * printAliases - print aliases
 * @data: data holder
 * @alias: print an alias if null print all
 * Return: 1 (single print) | 0 (all)
 */
int printAliases(data_t *data, char *alias)
{
	int i, j, flag = 0, qflag = 0, len;

	for (i = 0; data->alias[i] != NULL; i++)
	{
		if (alias)
		{
			if (_strncmp(data->alias[i], alias, _strlen(alias)) == 0
					&& data->alias[i][_strlen(alias)] == '=')
			{
				flag = 1;
			}
			else
			{
				continue;
			}
		}
		len = _strlen(data->alias[i]);
		for (j = 0; j < len; j++)
		{
			switch (data->alias[i][j])
			{
				case '=':
					qflag = 1;
					break;
				default:
					_putchar(data->alias[i][j]);
					break;
			}
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
		{
			return (1);
		}
	}

	return (0);
}
/**
 * addAlias - add alias or overwrite existing
 * @data: data holder
 * @alia: new alias
 */
void addAlias(data_t *data, char *alia)
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
	{
		free(data->alias[i]);
	}
	else if (!flag)
	{
		len = _strlen(alia);
		data->alias[i] = malloc(sizeof(char) * (len + 3));
		if (data->alias[i] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			return;
		}

		_strcpy(data->alias[i], alia);
		data->alias[i][len] = '\0';
	}
}

