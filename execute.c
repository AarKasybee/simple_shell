#include "shell.h"
/**
 * execute - execute a command
 * @data: a pointer to the program's data
 * Return: If sucess returns zero
 */
int execute(data_of_program *data)
{
	int ret = 0, stat;
	pid_t pidd;

	ret = b_list(data);
	if (ret != -1)
		return (ret);

	ret = find(data);
	if (ret)
	{
		return (ret);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{
			ret = execve(data->tokens[0], data->tokens, data->env);
			if (ret == -1)
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stat);
			if (WIFEXITED(stat))
				errno = WEXITSTATUS(stat);
			else if (WIFSIGNALED(stat))
				errno = 128 + WTERMSIG(stat);
		}
	}
	return (0);
}

