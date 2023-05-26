#include "shell.h"
/**
 * interactivemode - simple shell interactive mode
 * @ac: arguments count
 * @data: data holder
 */
void interactivemode(int ac, data_t *data)
{
	int size = 0, line = 0, fd = 0;

	if (!data->modo && ac == 2) {
		fd = openFile(data);
	} else {
		fd = 0;
	}

	while ((line = fetchcommand(data, &size, fd)) != -1 || data->lineptr) {
		data->cmdCounter++;
		if (line == 0) {
			continue;
		}

		commentHandler(data);
		data->lineptr = opSep(data);
		data->cmd = _strtok(data->lineptr, DELIM, &data->cmdSize);


		if (data->cmdSize > 0)
		{
			specialVarHandler(data);
			handleprocess(data);
			freeSarray(data->cmd, data->cmdSize);
			data->cmd = NULL;
			free(data->lineptr);
			data->lineptr = NULL;
		}
	}
	if (!data->modo && ac == 2)
		closeFile(data, fd);
	freeData(data);
}
/**
 * handleprocess - fork and handle parent/child process
 * also handle operands && and ||
 * @data: data holder
 */
void handleprocess(data_t *data)
{
	int stat = 0, i = 0, j, k = 0, f = 0, Count = commandsCounter(data);
	int cmp2 = 0, cmp = 0, sep = 0, Cpos = 0, isBI = 0, pos = 0, m;
	char *exe = NULL, *ptr[64];

	while (i < Count)
	{
		j = processHelper(data, ptr, &i, &pos, &Count, &cmp2);
		if (i == 0 || (stat == 0 && cmp == 0) || ((sep & 2) && stat == 0)
				|| ((sep & 4) && stat != 0) || (sep & 1))
		{
			Cpos = cmp2 == 0 ? 0 : 1;
			ptr[0] = aliasHandler(data, pos);
			if (i == Count - 1)
			{
				m = 0;
				while (ptr[m] != NULL)
					m++;
				if (_strcmp(ptr[m - 1], ";") == 0)
					ptr[m - 1] = NULL;
			}
			isBI = built(data, ptr[0], i + Cpos);
			if (isBI)
			{
				i++;
				continue;
			}
			exe = exeFixer(ptr[0], data);
			if (!isBI && !isDir(ptr[0]) && exe != NULL)
				forking(data, ptr, exe, &stat);
			else
				Notfound(data);
		}
		sep = 0;
		while (i < Count - 1 && data->cmd[pos + k] != NULL)
		{
			cmp = tokCompare(data->cmd[pos + k], &sep, &f);
			if (cmp != 0)
			{
				k--;
				break;
			}
			k++;
		}
		pos += j + 1;
		i++;
	}
}
/**
 * processHelper - check for separators and operators
 * @data: data holder
 * @ptr: pointer to first argument in the command
 * @i: number of commands index
 * @pos: position of the command in the array of commands
 * @c: number of commands
 * @cmp2: the number of the sep/operator
 * Return: int
 */
int processHelper(data_t *data, char **ptr, int *i, int *pos,
		int *c, int *cmp2)
{
	int j = 0;

	while (data->cmd[(*pos) + j] != NULL)
	{
		if ((*i) < (*c) - 1)
		{
			*cmp2 = tokChecker(data->cmd[(*pos) + j]);
			if ((*cmp2) != 0)
				break;
		}
		ptr[j] = data->cmd[(*pos) + j];
		j++;
	}
	ptr[j] = NULL;
	return j;
}
/**
 * forking - make a child process for the command to execute
 * @data: data holder
 * @cmd: command line
 * @exe: the path to the exe
 * @stat: status
 * Return: the status of the execution
 */
void forking(data_t *data, char **cmd, char *exe, int *stat)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /* child process */
	{
		*stat = execve(exe, cmd, data->envp);
		if (*stat == -1)
		{
			perror(exe);
			exit(EXIT_FAILURE);
		}
	}
	else /* parent process */
	{
		while (waitpid(pid, &status, 0) == -1)
		{
			if (errno != EINTR)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}

		if (WIFEXITED(status))
			*stat = WEXITSTATUS(status);

		if (data->flag)
		{
			free(exe);
			exe = NULL;
		}
	}
}

