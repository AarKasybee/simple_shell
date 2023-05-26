/**
 * set_environment_variable - Set or modify an environment variable
 * @data: Data holder
 * @name: Variable name
 * @value: Value of the variable
 */
void set_environment_variable(data_t *data, char *name, char *value)
{
	int i, len;
	char flag = 0;

	if (name != NULL && value != NULL)
	{
		for (i = 0; data->envp[i] != 0; i++)
		{
			if (compare_environment_variable(data->envp[i], name))
			{
				free(data->envp[i]);
				flag = 1;
				break;
			}
		}
		len = string_length(name) + string_length(value) + 1;
		data->envp[i] = malloc(len + 1);
		if (data->envp[i] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			exit(128);
		}
		copy_string(data->envp[i], name);
		concatenate_string(data->envp[i], "=");
		concatenate_string(data->envp[i], value);
		data->envp[i][len] = '\0';

		if (!flag)
			data->envp[i + 1] = NULL;
	}
}

/**
 * set_current_working_directory - Set the current working directory
 * @data: Data holder
 * @new_directory: New working directory
 * @p: New or -
 * Return: 0 (success) | 1 (failure)
 */
int set_current_working_directory(data_t *data, char *new_directory, int p)
{
	int status = 0, pos = 0;
	char previous_directory[128] = {'\0'};

	getcwd(previous_directory, 128);
	if (compare_strings(previous_directory, new_directory) != 0)
	{
		pos = find_character_position(new_directory, '=');
		status = chdir(new_directory + pos + p);
		if (status == -1)
		{
			print_string(data->prog_name, 2);
			print_string(": ", 2);
			print_integer(data->cmd_counter, 2);
			print_string(": cd: can't cd to ", 2);
			print_string(new_directory + pos + p, 2);
			print_string("\n", 2);
			errno = 2;
			return (1);
		}
		set_environment_variable(data, "PWD", new_directory + pos + p);
	}
	if (p)
	{
		print_string(new_directory + pos + p, 1);
		print_string("\n", 1);
	}
	pos = find_character_position(previous_directory, '=');
	set_environment_variable(data, "OLDPWD", previous_directory + pos);
	return (0);
}

