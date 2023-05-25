#include "headers.h"

void call_parent(pid_t pid);

/**
 * fork_new_process - forks a new process within the parent process
 *@command: an array of user input characters in the user command
 *@path: an array of paths to search for executable programs
 *
 * Return: void
 */
void fork_new_process(char **command, char **path)
{
	pid_t pid;

	exit_func(command);
	env_func(command);

	if (access(command[0], X_OK) != 0)
	{
		char executable_path[MAX_PATH_LENGTH];
		int i;

		for (i = 0; path[i] != NULL; i++)
		{
			_snprintf(path[i], command[0], executable_path);
			if (access(executable_path, X_OK) == 0)
			{
				break;
			}
		}
		if (path[i] == NULL)
		{
			_puts("./shell: No such file or directory");
			_puts("\n");
			return;
		}
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
	}
	else if (pid == 0) /* child process*/
	{
		char executable_path[MAX_PATH_LENGTH];
		int i;

		execve(command[0], command, NULL);
		for (i = 0; path[i] != NULL; i++)
		{
			_snprintf(path[i], command[0], executable_path);
			execve(executable_path, command, NULL);
		}
		perror("./shell: "); /*if execve returns, it must have failed*/
		exit(1);
	}
	else /*parent process*/
	{
		call_parent(pid);
	}
}

/**
 * call_parent - start the parent process
 * @pid: process id
 * Return: void
 */
void call_parent(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);
		char _exit_status[10];

		int_to_str(exit_status, _exit_status);

		if (exit_status != 0)
		{
			_puts("./shell: No such file or directory");
			_puts("\n");
		}
	}
	else if (WIFSIGNALED(status))
	{
		int signal_number = WTERMSIG(status);
		char _signal_number[10];

		int_to_str(signal_number, _signal_number);
		_puts("./shell: No such file or directory");
		_puts("\n");
	}
}

