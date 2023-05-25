#include "headers.h"

/**
 * _getenv - retrieves the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if not found
 */
char *_getenv(const char *name)
{
        extern char **environ;
        size_t name_len = strlen(name);

        if (environ != NULL && name != NULL)
        {
		char **env;
                for (env = environ; *env != NULL; env++)
                {
                        if (strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
                        {
                                return &((*env)[name_len + 1]);
                        }
                }
        }
        return NULL;
}
