#include "shell.h"

/**
 * get_environment_variable - Get environment variable value
 * @var: Variable
 * @data: Data holder
 * Return: String
 */
char *get_environment_variable(char *var, data_t *data)
{
	int i, len;

	len = string_length(var);
	for (i = 0; data->envp[i]; i++)
	{
		if (string_n_compare(data->envp[i], var, len) == 0)
		{
			return (data->envp[i]);
		}
	}

	return (NULL);
}

/**
 * copy_environment - Make a copy of the environment variables
 * @env_copy: Environment copy
 * @envp: Pointer to environment
 * Return: Copy | NULL
 */
char **copy_environment(char **env_copy, char **envp)
{
	int i;

	if (envp == NULL)
		return (NULL);

	for (i = 0; envp[i]; i++)
	{
		env_copy[i] = string_duplicate(envp[i]);
	}

	return (env_copy);
}

/**
 * compare_environment_variable - Check if the variable exists
 * @env_var: Pointer to the environment variable
 * @var: Variable to check
 * Return: Variable | NULL
 */
char *compare_environment_variable(char *env_var, char *var)
{
	int len;

	if (env_var == NULL || var == NULL)
		return (NULL);

	len = string_length(var);

	if (string_n_compare(var, env_var, len) == 0 && env_var[len] == '=')
	{
		return (env_var);
	}

	return (NULL);
}

/**
 * count_environment_variables - Count the number of environment variables
 * @data: Data holder
 * Return: Integer
 */
int count_environment_variables(data_t *data)
{
	int i;

	for (i = 0; data->envp[i]; i++)
		;

	return (i);
}

