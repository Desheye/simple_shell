#include "shell.h"

ssize_t custom_input_buf(info_t *information, char **buffer, size_t *length) {
    ssize_t bytesRead = 0;
    size_t lengthPointer = 0;

    if (!*length) {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, custom_sigintHandler);

        bytesRead = getline(buffer, &lengthPointer, stdin);

        if (bytesRead > 0) {
            if ((*buffer)[bytesRead - 1] == '\n') {
                (*buffer)[bytesRead - 1] = '\0';
                bytesRead--;
            }

            information->linecount_flag = 1;
            custom_remove_comments(*buffer);
            custom_build_history_list(information, *buffer, information->histcount++);

            {
                *length = bytesRead;
                information->cmd_buf = buffer;
            }
        }
    }

    return bytesRead;
}

ssize_t custom_get_input(info_t *information) {
    static char *buffer;
    static size_t x, y, length;
    ssize_t bytesRead = 0;
    char **bufferPointer = &(information->arg), *p;

    _putchar(BUF_FLUSH);
    bytesRead = custom_input_buf(information, &buffer, &length);

    if (bytesRead == -1)
        return -1;

    if (length) {
        y = x;
        p = buffer + x;

        custom_check_chain(information, buffer, &y, x, length);

        while (y < length) {
            if (custom_is_chain(information, buffer, &y))
                break;
            y++;
        }

        x = y + 1;

        if (x >= length) {
            x = length = 0;
            information->cmd_buf_type = CMD_NORM;
        }

        *bufferPointer = p;
        return _strlen(p);
    }

    *bufferPointer = buffer;
    return bytesRead;
}

ssize_t custom_read_buf(info_t *information, char *buffer, size_t *i) {
    ssize_t bytesRead = 0;

    if (*i)
        return 0;

    bytesRead = read(information->readfd, buffer, READ_BUF_SIZE);

    if (bytesRead >= 0)
        *i = bytesRead;

    return bytesRead;
}

int custom_getline(info_t *information, char **pointer, size_t *length) {
    static char buffer[READ_BUF_SIZE];
    static size_t x, length;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *newP = NULL, *c;

    p = *pointer;

    if (p && length)
        s = *length;

    if (x == length)
        x = length = 0;

    r = custom_read_buf(information, buffer, &length);

    if (r == -1 || (r == 0 && length == 0))
        return -1;

    c = _strchr(buffer + x, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : length;
    newP = _realloc(p, s, s ? s + k : k + 1);

    if (!newP)
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(newP, buffer + x, k - x);
    else
        _strncpy(newP, buffer + x, k - x + 1);

    s += k - x;
    x = k;
    p = newP;

    if (length)
        *length = s;

    *pointer = p;
    return s;
}

void custom_sigintHandler(__attribute__((unused))int signalNumber) {
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

