#include "shell.h"

/**
 * exit_builtin - Exit the program
 * @data: Data holder
 * @idx: Command index
 * Return: 1 | Exit code (errno)
 */
int exit_builtin(data_t *data, int idx)
{
	int exit_code = 0;

	if (data->cmd[idx + 1] != NULL)
	{
		if (_isDigit(data->cmd[idx + 1]))
		{
			exit_code = _atoi(data->cmd[idx + 1]);
			free_data(data);
			exit(exit_code);
		}
		else
		{
			_puts(data->prog_name, 2);
			_puts(": ", 2);
			print_int(data->cmd_counter, 2);
			_puts(": ", 2);
			_puts(data->cmd[idx], 2);
			_puts(": Illegal number: ", 2);
			_puts(data->cmd[idx + 1], 2);
			_puts("\n", 2);
			free_data(data);
			exit(2);
		}
	}
	free_data(data);
	exit(errno);
	return (1);
}

/**
 * cd_builtin - cd built-in function
 * @data: Data holder
 * @idx: Command index
 * Return: 1 (success)
 */
int cd_builtin(data_t *data, UNUSED int idx)
{
	char *home_dir = _getenv("HOME=", data), old_pwd[128] = {'\0'};
	char *prev_dir = NULL;
	int status = 0, pos = 5;

	if (data->cmd[1])
	{
		if (_strcmp(data->cmd[1], "-") == 0)
		{
			prev_dir = _getenv("OLDPWD=", data);
			if (prev_dir != NULL)
				status = set_pwd(data, prev_dir, 1);
			else
			{
				_setenv(data, "OLDPWD", getcwd(old_pwd, 128));
				_puts(old_pwd + _strchr2(old_pwd, '=') + 1, 1);
				_puts("\n", 1);
			}
		}
		else
		{
			status = set_pwd(data, data->cmd[1], 0);
		}
	}
	else
	{
		if (home_dir == NULL)
		{
			pos = 0;
			home_dir = getcwd(old_pwd, 128);
		}
		status = set_pwd(data, home_dir + pos, 0);
	}

	return (status);
}

/**
 * env_builtin - Print the environment variables
 * @data: Data holder
 * @idx: Command index
 * Return: 1 (called)
 */
int env_builtin(data_t *data, UNUSED int idx)
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
 * setenv_builtin - Set an environment variable
 * @data: Data holder
 * @idx: Command index
 * Return: 1 (success)
 */
int setenv_builtin(data_t *data, int idx)
{
	int i, len;
	char flag = 0;

	if (data->cmd[idx + 1] != NULL && data->cmd[idx + 2] != NULL)
	{
		for (i = 0; data->envp[i] != 0; i++)
		{
			if (envcmp(data->envp[i], data->cmd[idx + 1]))
			{
				free(data->envp[i]);
				flag = 1;
				break;
			}
		}
		len = _strlen(data->cmd[idx + 1]) + _strlen(data->cmd[idx + 2]) + 1;
		data->envp[i] = malloc(len + 1);
		if (data->envp[i] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			return (1);
		}
		_strcpy(data->envp[i], data->cmd[idx + 1]);
		_strcat(data->envp[i], "=");
		_strcat(data->envp[i], data->cmd[idx + 2]);
		data->envp[i][len] = '\0';

		if (!flag)
			data->envp[i + 1] = NULL;
	}
	return (1);
}

/**
 * unsetenv_builtin - Unset an environment variable
 * @data: Data holder
 * @idx: Command index
 * Return: 1 (success)
 */
int unsetenv_builtin(data_t *data, int idx)
{
	int i, j;

	if (data->cmd[idx + 1] != NULL)
	{
		for (i = 0; data->envp[i] != 0; i++)
		{
			if (envcmp(data->envp[i], data->cmd[idx + 1]))
			{
				free(data->envp[i]);
				for (j = i + 1; data->envp[j] != NULL; j++)
					data->envp[j - 1] = data->envp[j];
				data->envp[j - 1] = NULL;
				break;
			}
		}
	}
	return (1);
}

