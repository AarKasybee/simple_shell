#ifndef SHELL_H
#define SHELL_H

#define EXIT "exit\n"

/********Libraries*********/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

/******modes_functions*****/
void nonInteractive(void);
void interactive(void);

/*******Functions**********/
void _getline(char **restrict lptr, size_t *restrict n, FILE *restrict strm);

/********str_helpers***********/
void _puts(char *s);
int _strlen(char *s, int j);
int _strcmp(char *s1, char *s2);


#endif
