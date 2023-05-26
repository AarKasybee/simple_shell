#include "shell.h"
/**
 * _getenv - get environment variable value
 * @var: variable
 * @data: data holder
 * Return: string
 */
char *_getenv(char *var, data_t *data)
{
	int i = 0;
	int len = _strlen(var);

	while (data->envp[i] != NULL)
	{
		if (_strncmp(data->envp[i], var, len) == 0)
		{
			return (data->envp[i]);
		}
		i++;
	}

	return (NULL);
}
/**
 * envcpy - make a copy of the environment variables
 * @envicopy: environment copy
 * @envp: pointer to environment
 * Return: copy | NULL
 */
char **envcpy(char **envicopy, char **envp)
{
	int i = 0;

	if (envp == NULL)
		return (NULL);

	while (envp[i] != NULL)
	{
		envicopy[i] = _strdup(envp[i]);
		i++;
	}

	return (envicopy);
}

/**
 * envcmp - check if the variable exists
 * @env: pointer to the environment variable
 * @var: variable to check
 * Return: variable | NULL
 */
char *envcmp(char *env, char *var)
{
	int len;

	if (env == NULL || var == NULL)
		return (NULL);

	len = _strlen(var);

	while (*env != '\0')
	{
		if (_strncmp(var, env, len) == 0 && env[len] == '=')
		{
			return (env);
		}
		env++;
	}

	return (NULL);
}
/**
 * envCount - environement Counter
 * @data: data holder
 * Return: integer
 */
int envCount(data_t *data)
{
	int i;

	for (i = 0; data->envp[i]; i++)
		;
	return (i);
}

