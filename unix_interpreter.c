#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100

/**
 * fork_new_process - forks a new process
 * @command: input from user
 *
 *
 * Return: void
 */
void fork_new_process(char command[MAX_COMMAND_LENGTH])
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
	}
	else if (pid == 0) /* child process*/
	{
		char *argv[] = {command, NULL};

		execve(command, argv, NULL);
		perror("./shell"); /*if execl returns, it must have failed*/
		exit(1);
	}
	else /*parent process*/
	{
		int status;

		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			if (exit_status != 0)
			{
				/*printf("Command '%s' failed with exit status %d\n",*/
				/*			  command, exit_status);*/
			}
		}
		else if (WIFSIGNALED(status))
		{
			int signal_number = WTERMSIG(status);

			 printf("Command '%s' was terminated by signal %d\n",
							 command, signal_number);
		}
	}
}

/**
 * main - Entry point to the shell program
 *
 * Return: success returns 0
 */
int main(void)
{
	char *command = NULL;
	size_t length = 0;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout); /* flush the output buffer */
		if (getline(&command, &length, stdin) == -1)
		{
			printf("\n");
			free(command);
			exit(0);
		}

		/* remove the newline character at the end of the command*/
		command[strcspn(command, "\n")] = 0;
		/* fork a new process*/
		fork_new_process(command);
	}

	free(command);
	return (0);
}
