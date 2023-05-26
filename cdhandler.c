#include "shell.h"


/**
 * _setenv - set or modify an environment variable
 * @name: variable name
 * @value: value of the variable
 * @data: data holder
 */
void _setenv(data_t *data, char *name, char *value)
{
    int i = 0;
    int len;
    char flag = 0;

    if (name != NULL && value != NULL)
    {
        while (data->envp[i] != 0)
        {
            if (envcmp(data->envp[i], name))
            {
                free(data->envp[i]);
                flag = 1;
                break;
            }
            i++;
        }
        len = _strlen(name) + _strlen(value) + 1;
        data->envp[i] = malloc(len + 1);
        if (data->envp[i] == NULL)
        {
            errno = ENOMEM;
            perror("Error");
            exit(128);
        }
        _strcpy(data->envp[i], name);
        _strcat(data->envp[i], "=");
        _strcat(data->envp[i], value);
        data->envp[i][len] = '\0';

        if (!flag)
            data->envp[i + 1] = NULL;
    }
}
/**
 * setPWD - set the current working directory
 * @data: data holder
 * @newDir: new working directory
 * @p: new or -
 * Return: 0 (success) | 1 (failed)
 */
int setPWD(data_t *data, char *newDir, int p)
{
    int stat = 0;
    int pos = 0;
    char prevdir[128] = {'\0'};

    getcwd(prevdir, 128);
    if (_strcmp(prevdir, newDir) != 0)
    {
        pos = _strchr2(newDir, '=');
        stat = chdir(newDir + pos + p);
        if (stat == -1)
        {
            _puts(data->progName, 2);
            _puts(": ", 2);
            print_int(data->cmdCounter, 2);
            _puts(": cd: can't cd to ", 2);
            _puts(newDir + pos + p, 2);
            _puts("\n", 2);
            errno = 2;
            return 1;
        }
        _setenv(data, "PWD", newDir + pos + p);
    }
    else
    {
        if (p)
        {
            _puts(newDir + pos + p, 1);
            _puts("\n", 1);
        }
    }
    pos = _strchr2(prevdir, '=');
    _setenv(data, "OLDPWD", prevdir + pos);
    return 0;
}

