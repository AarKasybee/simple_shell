#ifndef SHELL_H
#define SHELL_H

/********Libraries***************/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <fcntl.h>

/***********defines***************/
#define BUFFSIZE 128
#define DELIM " \t\n"
#define UNUSED __attribute__((unused))


/*******data_struct***************/
/**
 * data - struct holding program's data
 * @progName: program's name
 * @lineptr: line pointer
 * @cmd: command line tokenized
 * @envp: environment
 */
typedef struct data_t
{
	char *progName;
	char **argv;
	char *lineptr;
	char **cmd;
	int cmdSize;
	int cmdCounter;
	char **envp;
	char **alias;
	int flag;
	int modo;
	char *pewd;
} data_t;
/**
 * builtin_t - built-ins name and function
 * @name: name of the built-in
 * @f: the built-in's function
 */
typedef struct builtin_t
{
	char *name;
	int (*f)(data_t*, int);
} builtin_t;

/* ALIASES */
int my_aliases(data_t *data, int idx);
char *aliasHandler(data_t *data, int pos);
int printAliases(data_t *data, char *alias);
void addAlias(data_t *data, char *alia);

/* BUILTIN */
int built(data_t *data, char *cmd, int idx);
int (*get_builtin(char *cmd))(data_t*, int);

/*BUILTINFUNCTION*/
int builtin_exit(data_t *data, int idx);
int builtin_cd(data_t *data, UNUSED int idx);
int builtin_env(data_t *data, UNUSED int idx);
int builtin_setenv(data_t *data, int idx);
int builtin_unsetenv(data_t *data, int idx);

/*CDHANDLER*/
void _setenv(data_t *data, char *name, char *value);
int setPWD(data_t *data, char *newDir, int p);

/* ENVI */
char *_getenv(char *var, data_t *data);
char **envcpy(char **envicopy, char **envp);
char *envcmp(char *env, char *var);
int envCount(data_t *data);

/* FILE HANDLER */
int openFile(data_t *data);
void closeFile(data_t *data, int fd);

/* GET LINE */
int _getLine(data_t *data, int *size, int stream);
int lineHelper(data_t *data, int rd, int i);

/* HELPERS */
int tokChecker(char *tok);
int tokCompare(char *tok, int *sep, int *flag);
int commandsCounter(data_t *data);
char *exeFixer(char *cmd, data_t *data);

/* INTERACTIVE HANDLERS */
void interactivemode(int ac, data_t *data);
void handleprocess(data_t *data);
int processHelper(data_t *data, char **ptr, int *i, int *pos,int *c, int *cmp);
void forking(data_t *data, char **cmd, char *exe, int *stat);

/* LINE CHECK */
int isDir(char *path);
int _isDigit(char *s);
int _atoi(char *s);

/* MAIN */
int main(int argc, char *argv[], char *envp[]);
void dataInitialize(data_t *data, char *argv[], char *envp[]);
void handle_sig(UNUSED int sign);

/* MEM HANDLER */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strdup(char *str);
void freeData(data_t *data);
void freeSarray(char **arr, int size);
int checkOnlySpaces(char *line);

/* OPERATION HANDLER */
char *opSep(data_t *data);
void opChar(char *line, char *nline, int *idx, int *jmp);
void specialChar(char *line, char *nline, int *idx, int *jmp);
void commentHandler(data_t *data);

/* SPECIAL HANDLER */
void specialVarHandler(data_t *data);
void getVarValue(data_t *data, int idx);
void itobuff(char *buff, int val);

/* STRHANDLER */
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
int _strchr2(char *s, char c);
char *_strcat(char *dest, char *src);

/* STRTOK */
char **_strtok(char *str, const char *delim, int *size);
int countTok(char *str, const char *delim);
int tokLen(char *str, const char *delim, int index);
int isDelim(char c, const char *delim);

/* UTILS.c */
int fetchcommand(data_t *data, int *n, int stream);
char *_which(char *cmd, data_t *data);
void Notfound(data_t *data);

/* WRITE HANDLERS */
void _puts(char *s, int stream);
int _putchar(char c);
int _strlen(const char *s);
void print_int(int n, int stream);

#endif

