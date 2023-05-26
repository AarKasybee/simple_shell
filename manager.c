#include "shell.h"

/**
 * show_alias - show alias
 * @data: struct data
 * @alias: name of the alias
 * Return: zero if success
 */
int show_alias(data_of_program *data, char *alias)
{
	int i, j;
	char buffer[250];

	if (data->alias_list)
	{
		size_t alias_length = str_length(alias);

		for (i = 0; data->alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->alias_list[i], alias, alias_length)
						&& data->alias_list[i][alias_length] == '='))
			{
				for (j = 0; data->alias_list[i][j] && data->alias_list[i][j] != '='; j++)
				{
					buffer[j] = data->alias_list[i][j];
				}
				buffer[j] = '\0';
				_print(buffer);
				_print("'");
				_print(data->alias_list[i] + j + 1);
				_print("'\n");
			}
		}
	}

	return (0);
}

/**
 * take_alias - show alias
 * @data: struct
 * @name: name of the alias
 * Return: zero if sucess
 */
char *take_alias(data_of_program *data, char *name)
{
	int i, alias_length;


	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	alias_length = str_length(name);

	for (i = 0; data->alias_list[i]; i++)
	{
		if (str_compare(name, data->alias_list[i], alias_length) &&
				data->alias_list[i][alias_length] == '=')
		{
			return (data->alias_list[i] + alias_length + 1);
		}
	}

	return (NULL);

}

/**
 * fix_alias - set alias
 * @alias_string: alias to be set
 * @data: struct for the data
 * Return: zero if success
 */

int fix_alias(char *alias_string, data_of_program *data)
{
	int i, j;
	char buffer[250] = {'\0'};
	char *temp = NULL;

	if (alias_string == NULL || data->alias_list == NULL)
		return (1);


	for (i = 0; alias_string[i] && alias_string[i] != '='; i++)
		buffer[i] = alias_string[i];


	if (alias_string[i] == '=')
		temp = take_alias(data, alias_string + i + 1);


	for (j = 0; data->alias_list[j]; j++)
	{
		if (str_compare(buffer, data->alias_list[j], i) &&
				data->alias_list[j][i] == '=')
		{

			free(data->alias_list[j]);
			break;
		}
	}

	if (temp)
	{

		more_buffer(buffer, "=");
		more_buffer(buffer, temp);
		data->alias_list[j] = str_duplicate(buffer);
	}
	else
		data->alias_list[j] = str_duplicate(alias_string);

	return (0);
}

