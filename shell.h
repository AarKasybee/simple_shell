#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"


/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
} data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;
/*getline*/
int _getline(data_of_program *data);
int logic_op(char *array_commands[], int i, char array_operators[]);

/*aliasmgt*/
int show_alias(data_of_program *data, char *alias);
char *take_alias(data_of_program *data, char *alias);
int fix_alias(char *alias_string, data_of_program *data);

/*builtinenv*/
int unset_env(data_of_program *data);
int set_env(data_of_program *data);
int builtin(data_of_program *data);

/*builtinlist*/
int b_list(data_of_program *data);
int b_exit(data_of_program *data);

int b_cd(data_of_program *data);

int swd(data_of_program *data, char *new_dir);

int b_help(data_of_program *data);

int b_alias(data_of_program *data);

/*builtinmore*/
int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_work_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);
int builtin_alias(data_of_program *data);

/*envmanage*/
char *get_key(char *name, data_of_program *data);
int set_key(char *key, char *value, data_of_program *data);
int del_key(char *key, data_of_program *data);
void print_environ(data_of_program *data);

/* execute*/
int execute(data_of_program *data);

/*expansion*/
void expand_variables(data_of_program *data);
void enlarge_alias(data_of_program *data);
int more_buffer(char *buffer, char *str_to_add);

/*findinpath*/
char **tokenize_path(data_of_program *data);
int find(data_of_program *data);
int checker(char *full_path);

/*help1.c*/
void free_array_of_pointers(char **directories);
void free_data(data_of_program *data);
void free_the_data(data_of_program *data);

/*helpnum.c*/
void long_to_string(long number, char *string, int base);
int _atoi(char *s);
int count_characters(char *string, char *character);

/*help_p*/
int _print(char *string);
int _printer(char *string);
int _p_error(int errorcode, data_of_program *data);

/*help_str*/
int str_length(char *string);
char *str_duplicate(char *string);
int str_compare(char *string1, char *string2, int number);
char *str_concat(char *string1, char *string2);
void str_reverse(char *string);

/*main.c*/
void init_data(data_of_program *data, int arc, char *argv[], char **env);
void sis_ffo(char *prompt, data_of_program *data);
void handle_ctrl_c(int opr UNUSED);

/*strtoken.c & tokenize */
void tokenize(data_of_program *data);

char *_strtok(char *line, char *delim);


#endif
