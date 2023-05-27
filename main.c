#include "shell.h"
/**
 * main - initialize the variables
 * @argc: number of values received from the line
 * @argv: values received from the line
 * @env: number of values received from the line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	init_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	sis_ffo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * init_data - inicialize the struct with the info
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received
 */
void init_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int x = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;

	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printer(data->program_name);
			_printer(": 0: Can't open ");
			_printer(argv[1]);
			_printer("\n");
			exit(127);
		}
	}
	data->arguments = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[x]; x++)
		{
			data->env[x] = str_duplicate(env[x]);
		}
	}
	data->env[x] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (x = 0; x < 20; x++)
	{
		data->alias_list[x] = NULL;
	}
}
/**
 * sis_ffo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: infinite loop
 */
void sis_ffo(char *prompt, data_of_program *data)
{
	int error_ = 0, string_len = 0;

	while (++(data->exec_counter))
	{
		_print(prompt);
<<<<<<< HEAD
		error_ = string_len = _getline(data);
=======
		error_code = string_len = read_line(data);
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4

		if (error_ == EOF)
		{
			free_the_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			enlarge_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->arguments[0])
			{
				error_ = execute(data);
				if (error_ != 0)
					_p_error(error_, data);
			}
			free_data(data);
		}
	}
}

