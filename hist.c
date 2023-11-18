#include "shell.h"

char *custom_get_history_file(info_t *info) {
    char *home_directory, *history_file;

    home_directory = _getenv(info, "HOME=");
    if (!home_directory)
        return NULL;

    history_file = malloc(sizeof(char) * (_strlen(home_directory) + _strlen(HIST_FILE) + 2));
    if (!history_file)
        return NULL;

    history_file[0] = 0;
    _strcpy(history_file, home_directory);
    _strcat(history_file, "/");
    _strcat(history_file, HIST_FILE);

    return history_file;
}

int custom_write_history(info_t *info) {
    ssize_t file_descriptor;
    char *filename = custom_get_history_file(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (file_descriptor == -1)
        return -1;

    for (node = info->history; node; node = node->next) {
        _putsfd(node->str, file_descriptor);
        _putfd('\n', file_descriptor);
    }

    _putfd(BUF_FLUSH, file_descriptor);
    close(file_descriptor);

    return 1;
}

int custom_read_history(info_t *info) {
    int index, last = 0, line_count = 0;
    ssize_t file_descriptor, read_length, file_size = 0;
    struct stat file_stat;
    char *buffer = NULL, *filename = custom_get_history_file(info);

    if (!filename)
        return 0;

    file_descriptor = open(filename, O_RDONLY);
    free(filename);

    if (file_descriptor == -1)
        return 0;

    if (!fstat(file_descriptor, &file_stat))
        file_size = file_stat.st_size;

    if (file_size < 2)
        return 0;

    buffer = malloc(sizeof(char) * (file_size + 1));

    if (!buffer)
        return 0;

    read_length = read(file_descriptor, buffer, file_size);
    buffer[file_size] = 0;

    if (read_length <= 0)
        return free(buffer), 0;

    close(file_descriptor);

    for (index = 0; index < file_size; index++)
        if (buffer[index] == '\n') {
            buffer[index] = 0;
            custom_build_history_list(info, buffer + last, line_count++);
            last = index + 1;
        }

    if (last != index)
        custom_build_history_list(info, buffer + last, line_count++);

    free(buffer);
    info->hist_count = line_count;

    while (info->hist_count-- >= HIST_MAX)
        custom_delete_node_at_index(&(info->history), 0);

    custom_renumber_history(info);

    return info->hist_count;
}

int custom_build_history_list(info_t *info, char *buffer, int line_count) {
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    custom_add_node_end(&node, buffer, line_count);

    if (!info->history)
        info->history = node;

    return 0;
}

int custom_renumber_history(info_t *info) {
    list_t *node = info->history;
    int index = 0;

    while (node) {
        node->num = index++;
        node = node->next;
    }

    return info->hist_count = index;
}

