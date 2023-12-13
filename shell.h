#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer sizes for read/write operations */
#define BUFFER_SIZE_READ 1024
#define BUFFER_SIZE_WRITE 1024
#define BUFFER_FLUSH -1

/* Constants for command chaining types */
#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Flags for number conversion */
#define FLAG_LOWERCASE 1
#define FLAG_UNSIGNED 2

/* Configuration for getline() and strtok() */
#define CONFIG_USE_GETLINE 0
#define CONFIG_USE_STRTOK 0

/* Constants for history file and maximum entries */
#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * struct list_s - singly linked list
 * @index: numerical index
 * @data: string data
 * @next: next node in list
 */
typedef struct list_s
{
    int index;
    char *data;
    struct list_s *next;
} list_t;

/**
 * struct info_s - contains pseudo-arguments for function pointers
 * @cmd: command string
 * @args: array of command arguments
 * @cmd_path: path of the command
 * @arg_count: count of arguments
 * @line_num: current line number
 * @exit_code: exit code of last command
 * @count_line: flag for line counting
 * @file_name: name of the file being executed
 * @env_list: list of environment variables
 * @custom_environ: modified environment variables
 * @history_list: list of command history
 * @alias_list: list of aliases
 * @env_modified: flag indicating environment change
 * @last_status: last execution status
 * @command_buffer: buffer for command chaining
 * @buffer_type: type of command buffer
 * @input_fd: file descriptor for input
 * @history_count: count of history entries
 */
typedef struct info_s
{
    char *cmd;
    char **args;
    char *cmd_path;
    int arg_count;
    unsigned int line_num;
    int exit_code;
    int count_line;
    char *file_name;
    list_t *env_list;
    list_t *history_list;
    list_t *alias_list;
    char **custom_environ;
    int env_modified;
    int last_status;
    char **command_buffer;
    int buffer_type;
    int input_fd;
    int history_count;
} info_t;

#define INFO_INITIALIZER \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin_command - maps a string to a function
 * @cmd: command string
 * @func: pointer to function handling the command
 */
typedef struct builtin_command
{
    char *cmd;
    int (*func)(info_t *);
} builtin_cmd_t;


/* Main Shell Loop */
int execute_shell(info_t *, char **);
int locate_builtin(info_t *);
void search_command(info_t *);
void execute_command(info_t *);

/* Parsing and Execution */
int validate_command(info_t *, char *);
char *duplicate_substring(char *, int, int);
char *search_path(info_t *, char *, char *);

/* Command Input and Processing */
ssize_t receive_input(info_t *);
int fetch_line(info_t *, char **, size_t *);
void handle_signal(int);

/* String Utilities */
int calculate_length(char *);
int compare_strings(char *, char *);
char *match_substring(const char *, const char *);
char *concatenate_strings(char *, char *);

/* String Manipulation */
char *copy_string(char *, char *);
char *duplicate_string(const char *);
void output_string(char *);
int output_character(char);

/* String Copy and Concatenation */
char *copy_characters(char *, char *, int);
char *concatenate_characters(char *, char *, int);
char *find_character(char *, char);

/* Tokenization and String Splitting */
char **split_string(char *, char *);
char **split_string_single_delim(char *, char);

/* Memory Management and Reallocation */
char *set_memory(char *, char, unsigned int);
void free_string_array(char **);
void *resize_memory(void *, unsigned int, unsigned int);

/* Buffer Management */
int buffer_free(void **);

/* String to Integer Conversion */
int is_interactive(info_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_int(char *);

/* Error Handling */
void print_error_string(char *);
int print_error_character(char);
int print_to_file_descriptor(char, int);
int print_string_file_descriptor(char *, int);

/* Error Handling and Conversion */
int error_string_to_int(char *);
void display_error(info_t *, char *);
int print_decimal(int, int);
char *convert_to_string(long int, int, int);
void strip_comments(char *);

/* Built-in Commands */
int command_exit(info_t *);
int command_change_directory(info_t *);
int command_help(info_t *);

/* More Built-in Commands */
int command_history(info_t *);
int command_alias(info_t *);

/* Input Handling */
ssize_t process_input(info_t *);
int read_line(info_t *, char **, size_t *);
void signal_interrupt_handler(int);

/* Information Processing */
void initialize_info(info_t *);
void update_info(info_t *, char **);
void release_info(info_t *, int);

/* Environment Handling */
char *get_environment_variable(info_t *, const char *);
int print_environment(info_t *);
int set_environment_variable(info_t *);
int unset_environment_variable(info_t *);
int populate_environment_list(info_t *);

/* Environment Variable Management */
char **fetch_environment(info_t *);
int remove_environment_variable(info_t *, char *);
int create_environment_variable(info_t *, char *, char *);

/* Command History Management */
char *fetch_history_file(info_t *);
int save_history(info_t *);
int load_history(info_t *);
int add_to_history_list(info_t *, char *, int);
int renumber_command_history(info_t *);

/* List Operations */
list_t *prepend_node(list_t **, const char *, int);
list_t *append_node(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int delete_node_by_index(list_t **, unsigned int);
void destroy_list(list_t **);

/* Additional List Operations */
size_t calculate_list_length(const list_t *);
char **convert_list_to_string_array(list_t *);
size_t display_list(const list_t *);
list_t *find_node_with_prefix(list_t *, char *, char);
ssize_t find_node_index(list_t *, list_t *);

/* Variable Handling in Commands */
int detect_command_chain(info_t *, char *, size_t *);
void evaluate_command_chain(info_t *, char *, size_t *, size_t, size_t);
int substitute_alias(info_t *);
int substitute_variables(info_t *);
int replace_string_value(char **, char *);

#endif /* SHELL_H */

