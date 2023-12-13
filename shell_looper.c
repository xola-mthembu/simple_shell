#include "shell.h"

/**
 * shell_loop - central loop of the shell
 * @shell_info: struct containing info for the shell
 * @args: argument vector from main function
 * Return: 0 if successful, error code otherwise
 */
int shell_loop(info_t *shell_info, char **args)
{
    ssize_t read_status = 0;
    int builtin_status = 0;

    while (read_status != -1 && builtin_status != -2)
    {
        reset_info(shell_info);
        if (is_interactive_mode(shell_info))
            display_prompt();

        read_status = fetch_input(shell_info);
        if (read_status != -1)
        {
            initialize_info(shell_info, args);
            builtin_status = execute_builtin(shell_info);
            if (builtin_status == -1)
                execute_command(shell_info);
        }
        else if (is_interactive_mode(shell_info))
            print_newline();

        release_info(shell_info, 0);
    }

    save_history(shell_info);
    release_info(shell_info, 1);

    handle_exit_conditions(shell_info, builtin_status);
    return builtin_status;
}

/**
 * execute_builtin - searches and executes a builtin command
 * @shell_info: struct containing shell info
 * Return: status code of builtin execution
 */
int execute_builtin(info_t *shell_info)
{
    int status = -1;
    builtin_table builtin_commands[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (int i = 0; builtin_commands[i].type; i++)
    {
        if (string_compare(shell_info->argv[0], builtin_commands[i].type) == 0)
        {
            increment_line_count(shell_info);
            status = builtin_commands[i].func(shell_info);
            break;
        }
    }
    return status;
}

/**
 * execute_command - finds and executes a command from PATH
 * @shell_info: struct containing shell info
 */
void execute_command(info_t *shell_info)
{
    char *cmd_path = NULL;
    int arg_count = 0;

    set_command_path(shell_info);
    for (int i = 0; shell_info->arg[i]; i++)
        if (!is_delimiter(shell_info->arg[i], " \t\n"))
            arg_count++;

    if (!arg_count)
        return;

    cmd_path = search_command_path(shell_info, get_env_value(shell_info, "PATH="), shell_info->argv[0]);
    if (cmd_path)
    {
        shell_info->path = cmd_path;
        launch_child_process(shell_info);
    }
    else
    {
        handle_command_not_found(shell_info);
    }
}

/**
 * launch_child_process - creates a child process to execute a command
 * @shell_info: struct containing shell info
 */
void launch_child_process(info_t *shell_info)
{
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        print_error_message("Error during forking");
        return;
    }

    if (child_pid == 0)
    {
        if (execve(shell_info->path, shell_info->argv, get_environ(shell_info)) == -1)
        {
            release_info(shell_info, 1);
            handle_exec_error();
            exit(1);
        }
    }
    else
    {
        wait_for_child(shell_info);
    }
}
