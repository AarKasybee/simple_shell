#include "shell.h"
/**
 * special_var_handler - Handle the value of the special variable
 * @data: Data holder
 */
void special_var_handler(data_t *data)
{
	int i, val, flag = 0;
	char buffer[24] = {'\0'};

	for (i = 0; data->cmd[i] != NULL; i++)
	{
		if (_strcmp(data->cmd[i], "$$") == 0)
		{
			if (data->cmd[i])
				free(data->cmd[i]);
			val = getpid();
			int_to_buffer(buffer, val);
			flag = 1;
		}
		else if (_strcmp(data->cmd[i], "$?") == 0)
		{
			if (data->cmd[i])
				free(data->cmd[i]);
			int_to_buffer(buffer, errno);
			flag = 1;
		}
		else if (data->cmd[i][0] == '$'
			 && data->cmd[i][1] != ' ' && data->cmd[i][1] != '\0')
		{
			get_var_value(data, i);
			flag = 0;
		}
		if (flag)
		{
			data->cmd[i] = malloc(_strlen(buffer) + 1);
			data->cmd[i] = _strcpy(data->cmd[i], buffer);
			flag = 0;
		}
	}
}

/**
 * get_var_value - Compare if the variable is in the environment
 * @data: Data holder
 * @idx: Command index
 */
void get_var_value(data_t *data, int idx)
{
	int i;
	char var_name[48] = {'\0'}, *ptr = NULL;

	for (i = 1; data->cmd[idx][i] != '\0'; i++)
		var_name[i - 1] = data->cmd[idx][i];

	var_name[i] = '\0';

	ptr = _getenv(var_name, data);
	if (ptr != NULL)
	{
		free(data->cmd[idx]);
		 data->cmd[idx] = malloc(_strlen(ptr) + 1);
		 _strcpy(data->cmd[idx], ptr + _strlen(var_name) + 1);
	}
	else
	{
		data->cmd[idx][0] = '\0';
	}
}

/**
 * int_to_buffer - Convert integer to character buffer
 * @buff: Buffer
 * @val: Integer
 */
void int_to_buffer(char *buff, int val)
{
	int j = 0;

	do {
		buff[j++] = val % 10 + '0';
	} while ((val /= 10) > 0);
}

