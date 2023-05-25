#include "headers.h"

/**
 * main - Entry point to the shell program
 *
 * Return: success returns 0
 */
int main(void)
{
	char *command[MAX_COMMAND_LENGTH];
	char **path;
	char *token;
	int i;
	char *input = NULL;
	size_t input_size = 0;

	path = get_path();

	while (1)
	{
		_puts("#cisfun$ ");
		fflush(stdout); /*flush the output buffer*/
		if (getline(&input, &input_size, stdin) == -1) /**EOF*/
		{
			_puts("\n");
			free(input);
			exit(0);
		}
		if (_strcmp(input, "\n") == 0)
			continue;
		/* remove the newline character at the end of the command*/
		input[_strcspn(input, "\n")] = '\0';
		i = 0;
		token = _strtok(input, " ");
		while (token != NULL && i < MAX_COMMAND_LENGTH - 1)
		{
			command[i] = token;
			i++;
			token = _strtok(NULL, " ");
		}
		command[i] = NULL; /* terminate the array with a NULL pointer */
		fork_new_process(command, path);
	}
	free(input);
	return (0);
}

