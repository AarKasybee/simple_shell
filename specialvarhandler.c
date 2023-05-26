#include "shell.h"


/**
 * specialVarHandler - handle the value of the special variable
 * @data: data holder
 */
void specialVarHandler(data_t *data)
{
	int i = 0, val, flag = 0;
	char buffer[24] = {'\0'};

	while (data->cmd[i] != NULL)
	{
		if (_strcmp(data->cmd[i], "$$") == 0)
		{
			if (data->cmd[i])
				free(data->cmd[i]);
			val = getpid();
			itobuff(buffer, val);
			flag = 1;
		}
		else if (_strcmp(data->cmd[i], "$?") == 0)
		{
			if (data->cmd[i])
				free(data->cmd[i]);
			itobuff(buffer, errno);
			flag = 1;
		}
		else if (data->cmd[i][0] == '$'
			 && data->cmd[i][1] != ' ' && data->cmd[i][1] != '\0')
		{
			getVarValue(data, i);
			flag = 0;
		}
		if (flag)
		{
			data->cmd[i] = malloc(_strlen(buffer) + 1);
			data->cmd[i] = _strcpy(data->cmd[i], buffer);
			flag = 0;
		}
		i++;
	}
}


/**
 * getVarValue - compare if the variable is in the environment
 * @data: data holder
 * @idx: command index
 */
void getVarValue(data_t *data, int idx)
{
	int i = 1;
	char varName[48] = {'\0'}, *ptr = NULL;

	while (data->cmd[idx][i] != '\0')
	{
		varName[i - 1] = data->cmd[idx][i];
		i++;
	}

	varName[i] = '\0';

	ptr = _getenv(varName, data);
	if (ptr != NULL)
	{
		free(data->cmd[idx]);
		data->cmd[idx] = malloc(_strlen(ptr) + 1);
		_strcpy(data->cmd[idx], ptr + _strlen(varName) + 1);
	}
	else
	{
		data->cmd[idx][0] = '\0';
	}
}

/**
 * itobuff - int to char buffer
 * @buff: buffer
 * @val: integer
 */
void itobuff(char *buff, int val)
{
	int j = 0;

	do 
    {
		buff[j++] = val % 10 + '0';
	} while ((val /= 10) > 0);
}

