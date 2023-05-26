#include "shell.h"
/**
 * main - simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment
 * Return: int
 */
int main(int argc, char *argv[], char *envp[])
{
	data_t data;

	signal(SIGINT, handle_sig);

	if (isatty(STDIN_FILENO) && argc == 1)
	{
		data.modo = 1;
	}
	else
	{
		data.modo = 0;
	}

	errno = 0;

	dataInitialize(&data, argv, envp);

	while (1)
	{
		interactivemode(argc, &data);

		if (data.lineptr == NULL)
		{
			break;
		}

		free(data.lineptr);
		data.lineptr = NULL;
		data.cmdCounter++;
	}

	return 0;
}
/**
 * dataInit - data
 * @data: data holder
 * @argv: arguments array
 * @envp: environemnt array
 */
void dataInitialize(data_t *data, char *argv[], char *envp[])
{
	int i;

	/*initialize data*/
	data->progName = argv[0];
	data->argv = argv;

	/*copy envp*/
	data->envp = malloc(sizeof(char *) * 64);

	if (data->envp != NULL)
	{
		for (i = 0; i < 64; i++)
			data->envp[i] = NULL;

		envcpy(data->envp, envp);
		envp = data->envp;
	}

	/** alias **/
	data->alias = malloc(sizeof(char *) * 24);

	if (data->alias != NULL)
	{
		for (i = 0; i < 24; i++)
			data->alias[i] = NULL;
	}

	data->lineptr = NULL;
	data->cmd = NULL;
	data->cmdSize = 0;
	data->cmdCounter = 0;
}
/**
 * handle_sig - handle sign
 * @sign: sign
 */
void handle_sig(UNUSED int sign)
{
	_puts("\n", 1);
	_puts("$ ", 1);
}

