#include "shell.h"

/**
 * b_exit - exit of the program
 * @data: struct for the program
 * Return: zero if sucess
 */
int b_exit(data_of_program *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
					&& data->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = string_to_integer(data->tokens[1]);
	}
	free_the_data(data);
	exit(errno);
}

/**
 * b_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess
 */
int b_cd(data_of_program *data)
{
	char *dir_home = get_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = get_key("OLDPWD", data);
			if (dir_old)
				error_code = swd(data, dir_old);
			_print(get_key("PWD", data));
			_print("\n");

			return (error_code);
		}
		else
		{
			return (swd(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (swd(data, dir_home));
	}
	return (0);
}

/**
 * swd - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess
 */
int swd(data_of_program *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		set_key("PWD", new_dir, data);
	}
	set_key("OLDPWD", old_dir, data);
	return (0);
}

/**
 * b_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess
 */
int b_help(data_of_program *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[i], length))
		{
			_print(mensajes[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * b_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess
 */
int b_alias(data_of_program *data)
{
	int i = 0;

	if (data->tokens[1] == NULL)
		return (show_alias(data, NULL));

	while (data->tokens[++i])
	{
		if (count_occurrences(data->tokens[i], "="))
			fix_alias(data->tokens[i], data);
		else
			show_alias(data, data->tokens[i]);
	}
	return (0);
}

