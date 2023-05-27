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

<<<<<<< HEAD
	ret = b_list(data);
	if (ret != -1)
		return (ret);
=======
	retval = search_builtin(data);
	if (retval != -1)
		return (retval);
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4

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
<<<<<<< HEAD
			ret = execve(data->tokens[0], data->tokens, data->env);
			if (ret == -1)
=======
			retval = execve(data->arguments[0], data->arguments, data->env);
			if (retval == -1)
>>>>>>> 68d70272a3cec7e304ffc9b7910c5ef8812193d4
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

