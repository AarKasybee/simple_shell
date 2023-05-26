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

int handle_builtin_aliases(data_t *data, int idx);
char *alias_handler(data_t *data, int pos);
int print_aliases(data_t *data, char *alias);
void add_alias(data_t *data, char *alia);

int check_builtin(data_t *data, char *cmd, int idx);
int (*get_builtin_function(char *cmd))(data_t *, int);

int exit_builtin(data_t *data, int idx);
int cd_builtin(data_t *data, UNUSED int idx);
int env_builtin(data_t *data, UNUSED int idx);
int setenv_builtin(data_t *data, int idx);
int unsetenv_builtin(data_t *data, int idx);

void set_environment_variable(data_t *data, char *name, char *value);
int set_current_working_directory(data_t *data, char *new_directory, int p);

char *get_environment_variable(char *var, data_t *data);
char **copy_environment(char **env_copy, char **envp);
char *compare_environment_variable(char *env_var, char *var);
int count_environment_variables(data_t *data);

int fileopen(data_t *data);
void fileclose(data_t *data, int fd);

int custom_readLine(data_t *data, int *size, int stream);
int custom_helper(data_t *data, int read_count, int i);

int checkOnlySpaces(char *line);

char *fix_executable_path(char *cmd, data_t *data);
int count_commands(data_t *data);
int compare_token(char *tok, int *sep, int *flag);
int check_token(char *tok);


void run_interactive_mode(int argc, data_t *data);
void handle_processes(data_t *data);
int process_helper(data_t *data, char **ptr, int *i, int *pos, int *c, int *cmp2);
void fork_process(data_t *data, char **cmd, char *exe, int *stat);

int is_directory(char *path);
int is_digit(char *s);
int atoi_custom(char *s);


int main(int argc, char *argv[], char *envp[]);
void initialize_data(data_t *data, char *argv[], char *envp[]);
void handle_signal(UNUSED int sign);

char *_mem_copy(char *dest, char *src, unsigned int n);
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char *_str_duplicate(char *str);
void free_data(data_t *data);
void free_string_array(char **arr, int size);


char *separate_operator(data_t *data);
void separate_char(char *line, char *newLine, int *idx, int *jmp);
void special_char(char *line, char *newLine, int *idx, int *jmp);
void comment_handler(data_t *data);

void special_var_handler(data_t *data);
void get_var_value(data_t *data, int idx);
void int_to_buffer(char *buff, int val);

int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, const char *src);
int _strchr2(const char *s, int c);
char *_strcat(char *dest, const char *src);

char **custom_strtok(char *str, const char *delim, int *size);
int countTokens(char *str, const char *delim);
int getTokenLength(char *str, const char *delim, int index);
int isDelimiter(char c, const char *delim);

int prompt(data_t *data, int *n, int stream);
char *_which(char *cmd, data_t *data);
void Notfound(data_t *data);

void _puts(char *s, int stream);
int _putchar(char c);
int _strlen(const char *s);
void print_int(int n, int stream);

#endif
