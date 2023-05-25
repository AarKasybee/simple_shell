#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <stddef.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_PATH_LENGTH 100

size_t _strcspn(const char *str1, const char *str2);
void _puts(char *str);
int _putchar(char c);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strtok(char *str, const char *delim);
void int_to_str(int num, char *str);
extern char **environ;
void exit_func(char **command);
void env_func(char **command);
int _snprintf(char *input_str, char *input_str2, char *str_buf);
void fork_new_process(char **command, char **path);

char **get_path();
char *_getenv(char *name);
char *_getenv1(const char *name);
#endif
