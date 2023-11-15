#include "shell.h"

char *getHistoryFilePath(info_t *info)
{
    char *homeDir = _getenv(info, "HOME=");
    if (!homeDir)
        return NULL;

    char *filePath = malloc(sizeof(char) * (customStrlen(homeDir) + customStrlen(HISTORY_FILE) + 2));
    if (!filePath)
        return NULL;

    customStrcpy(filePath, homeDir);
    customStrcat(filePath, "/");
    customStrcat(filePath, HISTORY_FILE);

    return filePath;
}

int writeHistoryToFile(info_t *info)
{
    ssize_t fd;
    char *filename = getHistoryFilePath(info);
    list_t *node = NULL;

    if (!filename)
        return -1;

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return -1;

    for (node = info->history; node; node = node->next)
    {
        printStringToFile(node->str, fd);
        printCharToFile('\n', fd);
    }

    printCharToFile(BUFFER_FLUSH, fd);
    close(fd);

    return 1;
}

int readHistoryFromFile(info_t *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = getHistoryFilePath(info);

    if (!filename)
        return 0;

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return 0;

    if (!fstat(fd, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return 0;

    buf = malloc(sizeof(char) * (fsize + 1));

    if (!buf)
        return 0;

    rdlen = read(fd, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return free(buf), 0;

    close(fd);

    for (i = 0; i < fsize; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            buildHistoryList(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        buildHistoryList(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= HISTORY_MAX)
        deleteNodeAtIndex(&(info->history), 0);

    renumberHistory(info);

    return info->histcount;
}

int buildHistoryList(info_t *info, char *buf, int linecount)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;

    addNodeEnd(&node, buf, linecount);

    if (!info->history)
        info->history = node;

    return 0;
}

int renumberHistory(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }

    return info->histcount = i;
}
