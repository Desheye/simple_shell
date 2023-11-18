#include "shell.h"

int is_chain(info_t *info, char *buffer, size_t *position) {
    size_t index = *position;

    if (buffer[index] == '|' && buffer[index + 1] == '|') {
        buffer[index] = 0;
        index++;
        info->cmd_buf_type = CMD_OR;
    } else if (buffer[index] == '&' && buffer[index + 1] == '&') {
        buffer[index] = 0;
        index++;
        info->cmd_buf_type = CMD_AND;
    } else if (buffer[index] == ';') {
        buffer[index] = 0;
        info->cmd_buf_type = CMD_CHAIN;
    } else {
        return 0;
    }

    *position = index;
    return 1;
}

void check_chain(info_t *info, char *buffer, size_t *position, size_t start, size_t length) {
    size_t index = *position;

    if (info->cmd_buf_type == CMD_AND) {
        if (info->status) {
            buffer[start] = 0;
            index = length;
        }
    }

    if (info->cmd_buf_type == CMD_OR) {
        if (!info->status) {
            buffer[start] = 0;
            index = length;
        }
    }

    *position = index;
}

int replace_alias(info_t *info) {
    int t;
    list_t *node;
    char *str;

    for (t = 0; t < 10; t++) {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return 0;

        free(info->argv[0]);
        str = _strchr(node->str, '=');

        if (!str)
            return 0;

        str = _strdup(str + 1);

        if (!str)
            return 0;

        info->argv[0] = str;
    }

    return 1;
}

int replace_vars(info_t *info) {
    int t = 0;
    list_t *node;

    for (t = 0; info->argv[t]; t++) {
        if (info->argv[t][0] != '$' || !info->argv[t][1])
            continue;

        if (!_strcmp(info->argv[t], "$?")) {
            replace_string(&(info->argv[t]), _strdup(convert_number(info->status, 10, 0)));
            continue;
        }

        if (!_strcmp(info->argv[t], "$$")) {
            replace_string(&(info->argv[t]), _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }

        node = node_starts_with(info->env, &info->argv[t][1], '=');

        if (node) {
            replace_string(&(info->argv[t]), _strdup(_strchr(node->str, '=') + 1));
            continue;
        }

        replace_string(&info->argv[t], _strdup(""));
    }

    return 0;
}

int replace_string(char **old, char *new) {
    free(*old);
    *old = new;
    return 1;
}

