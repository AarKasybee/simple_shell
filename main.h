#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_PATH_LENGTH 100
extern char **environ;
void exit_func(char **command);
void env_func(char **command);

void fork_new_process(char **command, char **path);

char **get_path();
ssize_t _getline(char **restrict lineptr, size_t *restrict n,
		FILE * restrict stream);

#endif /*MAIN_H*/
