#include "shell.h"

/**
 * main - Simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment
 * Return: Integer
 */
int main(int argc, char *argv[], char *envp[])
{
	data_t data;

	signal(SIGINT, handle_signal);

	if (is_terminal(STDIN_FILENO) && argc == 1)
		data.is_interactive = 1;
	else
		data.is_interactive = 0;

	errno = 0;

	initialize_data(&data, argv, envp);

	interactive_mode(argc, &data);

	return (0);
}

/**
 * initialize_data - Initialize data structure
 * @data: Data holder
 * @argv: Arguments array
 * @envp: Environment array
 */
void initialize_data(data_t *data, char *argv[], char *envp[])
{
	int i;

	/* Initialize data */
	data->program_name = argv[0];
	data->argv = argv;

	/* Copy envp */
	data->envp = malloc(sizeof(char *) * 64);

	for (i = 0; i < 64; i++)
		data->envp[i] = NULL;

	copy_environment(data->envp, envp);
	envp = data->envp;

	/** Alias **/
	data->alias = malloc(sizeof(char *) * 24);
	for (i = 0; i < 24; i++)
		data->alias[i] = NULL;

	data->lineptr = NULL;
	data->cmd = NULL;
	data->cmd_size = 0;
	data->cmd_counter = 0;
}

/**
 * handle_signal - Handle signal
 * @sign: Signal
 */
void handle_signal(UNUSED int sign)
{
	_puts("\n", 1);
	_puts("$ ", 1);
}

