#include "shell.h"

/**
 * run_interactive_mode - Run the simple shell in interactive mode
 * @argc: Arguments count
 * @data: Data holder
 */
void run_interactive_mode(int argc, data_t *data)
{
	int size = 0, line = 0, fd = 0;

	if (!data->mode && argc == 2)
		fd = open_file(data);

	while ((line = prompt(data, &size, fd)) != -1 || data->lineptr)
	{
		data->cmdCounter++;
		if (line == 0)
			continue;

		handle_comments(data);
		data->lineptr = separate_operators(data);
		data->cmd = _strtok(data->lineptr, DELIM, &data->cmdSize);

		if (data->cmdSize > 0)
		{
			handle_special_vars(data);
			handle_processes(data);
			free_sarray(data->cmd, data->cmdSize);
			data->cmd = NULL;
			free(data->lineptr);
			data->lineptr = NULL;
		}
	}

	if (!data->mode && argc == 2)
		close_file(data, fd);

	free_data(data);
}

/**
 * handle_processes - Fork and handle parent/child processes
 * Also handle operators && and ||
 * @data: Data holder
 */
void handle_processes(data_t *data)
{
	int stat = 0, i, j, k = 0, f = 0, count = count_commands(data);
	int cmp2 = 0, cmp = 0, sep = 0, cmdPos = 0, isBI = 0, pos = 0, m;
	char *exe = NULL, *ptr[64];

	for (i = 0; i < count; i++)
	{
		j = process_helper(data, ptr, &i, &pos, &count, &cmp2);
		if (i == 0 || (stat == 0 && cmp == 0) || ((sep  & 2) && stat == 0)
		    || ((sep & 4) && stat != 0) || (sep & 1))
		{
			cmdPos = cmp2 == 0 ? 0 : 1;
			ptr[0] = handle_alias(data, pos);
			if (i == count - 1)
			{
				for (m = 0; ptr[m] != NULL; m++)
					;
				if (_strcmp(ptr[m - 1], ";") == 0)
					ptr[m - 1] = NULL;
			}
			isBI = check_builtin(data, ptr[0], i + cmdPos);
			if (isBI)
				continue;
			exe = fix_executable_path(ptr[0], data);
			if (!isBI && !is_directory(ptr[0]) && exe != NULL)
				fork_process(data, ptr, exe, &stat);
			else
				not_found(data);
		}
		for (sep = 0; i < count - 1 && data->cmd[pos + k] != NULL; k++)
		{
			cmp = compare_token(data->cmd[pos + k], &sep, &f);
			if (cmp != 0)
			{
				k--;
				break;
			}
		}
		pos += j + 1;
	}
}

/**
 * process_helper - Check for separators and operators
 * @data: Data holder
 * @ptr: Pointer to the first argument in the command
 * @i: Number of commands index
 * @pos: Position of the command in the array of commands
 * @c: Number of commands
 * @cmp2: The number of the separator/operator
 * Return: Integer
 */
int process_helper(data_t *data, char **ptr, int *i, int *pos,
		  int *c, int *cmp2)
{
	int j;

	for (j = 0; data->cmd[(*pos) + j] != NULL; j++)
	{
		if ((*i) < (*c) - 1)
		{
			*cmp2 = check_token(data->cmd[(*pos) + j]);
			if ((*cmp2) != 0)
				break;
		}
		ptr[j] = data->cmd[(*pos) + j];
	}
	ptr[j] = NULL;
	return (j);
}

/**
 * fork_process - Make a child process for the command to execute
 * @data: Data holder
 * @cmd: Command line
 * @exe: The path to the executable
 * @stat: Status
 * Return: The status of the execution
 */
void fork_process(data_t *data, char **cmd, char *exe, int *stat)
{
	pid_t pid;

	pid = fork();
	if (pid == 0) /* Child */
	{
		*stat = execve(exe, cmd, data->envp);
		if (*stat == -1)
		{
			perror(exe);
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent */
	{
		wait(stat);
		if (WIFEXITED(*stat))
			errno = WEXITSTATUS(*stat);

		if (data->flag)
			free(exe);
		exe = NULL;
	}
}

