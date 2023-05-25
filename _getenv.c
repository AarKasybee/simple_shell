#include "headers.h"

/**
 * _getenv - retrieves the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if not found
 */
char *_getenv(char *name)
{
	size_t name_len = _strlen(name);

	if (environ != NULL && name != NULL)
	{
		char **env;

		for (env = environ; *env != NULL; env++)
		{
			if (_strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
			{
				return (&((*env)[name_len + 1]));
			}
		}
	}
	return (NULL);
}
