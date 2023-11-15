#include "shell.h"

ssize_t readInputBuffer(info_t *info, char **buffer, size_t *length)
{
    ssize_t bytesRead = 0;
    size_t bufferLength = 0;

    if (!*length)
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handleSigint);

#if USE_GETLINE
        bytesRead = getline(buffer, &bufferLength, stdin);
#else
        bytesRead = customGetline(info, buffer, &bufferLength);
#endif

        if (bytesRead > 0)
        {
            if ((*buffer)[bytesRead - 1] == '\n')
            {
                (*buffer)[bytesRead - 1] = '\0';
                bytesRead--;
            }

            info->linecount_flag = 1;
            removeComments(*buffer);
            buildHistoryList(info, *buffer, info->histcount++);

            *length = bytesRead;
            info->cmd_buffer = buffer;
        }
    }

    return bytesRead;
}

ssize_t getInput(info_t *info)
{
    static char *buffer;
    static size_t i, j, length;
    ssize_t bytesRead = 0;
    char **bufferPtr = &(info->arg), *p;

    printCharToFD(BUFFER_FLUSH);
    bytesRead = readInputBuffer(info, &buffer, &length);

    if (bytesRead == -1)
        return -1;

    if (length)
    {
        j = i;
        p = buffer + i;

        checkChain(info, buffer, &j, i, length);

        while (j < length)
        {
            if (isChain(info, buffer, &j))
                break;
            j++;
        }

        i = j + 1;

        if (i >= length)
        {
            i = length = 0;
            info->cmd_buffer_type = CMD_NORM;
        }

        *bufferPtr = p;
        return customStrlen(p);
    }

    *bufferPtr = buffer;
    return bytesRead;
}

ssize_t readBuffer(info_t *info, char *buffer, size_t *index)
{
    ssize_t bytesRead = 0;

    if (*index)
        return 0;

    bytesRead = read(info->readfd, buffer, READ_BUFFER_SIZE);

    if (bytesRead >= 0)
        *index = bytesRead;

    return bytesRead;
}

int customGetline(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t bytesRead = 0, totalBytesRead = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;

    if (p && length)
        bytesRead = *length;

    if (i == len)
        i = len = 0;

    bytesRead = readBuffer(info, buffer, &len);

    if (bytesRead == -1 || (bytesRead == 0 && len == 0))
        return -1;

    c = customStrchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : len;

    new_p = customRealloc(p, bytesRead, bytesRead ? bytesRead + k : k + 1);

    if (!new_p) /* MALLOC FAILURE! */
        return p ? free(p), -1 : -1;

    if (bytesRead)
        customStrncat(new_p, buffer + i, k - i);
    else
        customStrncpy(new_p, buffer + i, k - i + 1);

    bytesRead += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = bytesRead;

    *ptr = p;
    return bytesRead;
}

void handleSigint(__attribute__((unused)) int signalNumber)
{
    printString("\n");
    printString("$ ");
    printCharToFD(BUFFER_FLUSH);
}
