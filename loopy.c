#include "shell.h"

int custom_hsh(info_t *information, char **arguments) {
    ssize_t read_status = 0;
    int builtin_return = 0;

    while (read_status != -1 && builtin_return != -2) {
        custom_clear_info(information);
        if (custom_interactive(information))
            _puts("$ ");
        _eputchar(BUF_FLUSH);

        read_status = custom_get_input(information);

        if (read_status != -1) {
            custom_set_info(information, arguments);
            builtin_return = custom_find_builtin(information);

            if (builtin_return == -1)
                custom_find_cmd(information);
        } else if (custom_interactive(information))
            _putchar('\n');

        custom_free_info(information, 0);
    }

    custom_write_history(information);
    custom_free_info(information, 1);

    if (!custom_interactive(information) && information->status)
        exit(information->status);

    if (builtin_return == -2) {
        if (information->err_num == -1)
            exit(information->status);
        exit(information->err_num);
    }

    return builtin_return;
}

int custom_find_builtin(info_t *information) {
    int index, builtin_ret = -1;
    builtin_table builtintbl[] = {
        {"exit", custom_myexit},
        {"env", custom_myenv},
        {"help", custom_myhelp},
        {"history", custom_myhistory},
        {"setenv", custom_mysetenv},
        {"unsetenv", custom_myunsetenv},
        {"cd", custom_mycd},
        {"alias", custom_myalias},
        {NULL, NULL}
    };

    for (index = 0; builtintbl[index].type; index++)
        if (_strcmp(information->argv[0], builtintbl[index].type) == 0) {
            information->line_count++;
            builtin_ret = builtintbl[index].func(information);
            break;
        }

    return builtin_ret;
}

void custom_find_cmd(info_t *information) {
    char *path = NULL;
    int index, arg_count;

    information->path = information->argv[0];

    if (information->line_count_flag == 1) {
        information->line_count++;
        information->line_count_flag = 0;
    }

    for (index = 0, arg_count = 0; information->arg[index]; index++)
        if (!is_delim(information->arg[index], " \t\n"))
            arg_count++;

    if (!arg_count)
        return;

    path = custom_find_path(information, _getenv(information, "PATH="), information->argv[0]);

    if (path) {
        information->path = path;
        custom_fork_cmd(information);
    } else {
        if ((custom_interactive(information) || _getenv(information, "PATH=")
            || information->argv[0][0] == '/') && is_cmd(information, information->argv[0]))
            custom_fork_cmd(information);
        else if (*(information->arg) != '\n') {
            information->status = 127;
            custom_print_error(information, "not found\n");
        }
    }
}

void custom_fork_cmd(info_t *information) {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1) {
        perror("Error:");
        return;
    }

    if (child_pid == 0) {
        if (execve(information->path, information->argv, get_environ(information)) == -1) {
            custom_free_info(information, 1);
            if (errno == EACCES)
                exit(126);
            exit(1);
        }
    } else {
        wait(&(information->status));

        if (WIFEXITED(information->status)) {
            information->status = WEXITSTATUS(information->status);
            if (information->status == 126)
                custom_print_error(information, "Permission denied\n");
        }
    }
}

