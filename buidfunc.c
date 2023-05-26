#include "shell.h"

/**
 * builtin_exit - exit the program
 * @data: data holder
 * @idx: command index
 * Return: 1 | exit (errno)
 */
int builtin_exit(data_t *data, int idx)
{
	int exit_code = 0;

	if (data->cmd[idx + 1] != NULL)
	{
		char *arg = data->cmd[idx + 1];

		switch (_isDigit(arg))

		{
			case 1:
				exit_code = _atoi(arg);
				freeData(data);
				exit(exit_code);
				break;
			default:
				_puts(data->progName, 2);
				_puts(": ", 2);
				print_int(data->cmdCounter, 2);
				_puts(": ", 2);
				_puts(data->cmd[idx], 2);
				_puts(": Illegal number: ", 2);
				_puts(arg, 2);
				_puts("\n", 2);
				freeData(data);
				exit(2);
				break;
		}
	}

	freeData(data);
	exit(errno);
	return (1);
}
/**
 * builtin_cd - cd builtin function
 * @data: data holder
 * @idx: command index
 * Return: 1 (success)
 */
int builtin_cd(data_t *data, UNUSED int idx)
{
	char *home_dir = _getenv("HOME=", data);
	char *prev_dir = NULL;
	char oldpwd[128] = {'\0'};
	int status = 0;
	int pos = 5;

	if (data->cmd[1] != NULL)
	{
		char *arg = data->cmd[1];

		if (_strcmp(arg, "-") == 0)
		{
			prev_dir = _getenv("OLDPWD=", data);
			if (prev_dir != NULL)
				status = setPWD(data, prev_dir, 1);
			else
			{
				_setenv(data, "OLDPWD", getcwd(oldpwd, 128));
				_puts(oldpwd + _strchr2(oldpwd, '=') + 1, 1);
				_puts("\n", 1);
			}
		}
		else
		{
			status = setPWD(data, arg, 0);
		}
	}
	else
	{
		if (home_dir == NULL)
		{
			pos = 0;
			home_dir = getcwd(oldpwd, 128);
		}
		status = setPWD(data, home_dir + pos, 0);
	}

	return (status);
}

/**
 * builtin_env - print the environement variables
 * @data: data holder
 * @idx: command index
 * Return: 1 (called)
 */
int builtin_env(data_t *data, UNUSED int idx)
{
	int i = 0;

	for (; data->envp[i]; i++)
	{
		_puts(data->envp[i], 1);
		_puts("\n", 1);
	}
	return (1);
}
/**
 * builtin_setenv - set an environment variable
 * @data: data holder
 * @idx: command index
 * Return: 1 (success)
 */
int builtin_setenv(data_t *data, int idx)
{
	int i, len;
	char found = 0;

	if (data->cmd[idx + 1] != NULL && data->cmd[idx + 2] != NULL)
	{
		char *var = data->cmd[idx + 1];
		char *value = data->cmd[idx + 2];

		for (i = 0; data->envp[i] != NULL; i++)
		{
			if (envcmp(data->envp[i], var))
			{
				free(data->envp[i]);
				found = 1;
				break;
			}
		}

		len = _strlen(var) + _strlen(value) + 1;
		data->envp[i] = malloc(len + 1);
		if (data->envp[i] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			return (1);
		}

		_strcpy(data->envp[i], var);
		_strcat(data->envp[i], "=");
		_strcat(data->envp[i], value);
		data->envp[i][len] = '\0';

		if (!found)
			data->envp[i + 1] = NULL;
	}
	return (1);
}
/**
 * builtin_unsetenv - unset an environment variable
 * @data: data holder
 * @idx: command index
 * Return: 1 (success)
 */
int builtin_unsetenv(data_t *data, int idx)
{
	int i, j;

	if (data->cmd[idx + 1] != NULL)
	{
		i = 0;
		while (data->envp[i] != NULL)
		{
			if (envcmp(data->envp[i], data->cmd[idx + 1]))
			{
				free(data->envp[i]);
				j = i + 1;
				while (data->envp[j] != NULL)
				{
					data->envp[j - 1] = data->envp[j];
					j++;
				}
				data->envp[j - 1] = NULL;
				break;
			}
			i++;
		}
	}
	return (1);
}

