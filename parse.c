#include "shell.h"

int isExecutableCommand(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    return (st.st_mode & S_IFREG) ? 1 : 0;
}

char *duplicateSubstring(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];
    buf[k] = '\0';
    return buf;
}

char *findCommandInPath(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, currPos = 0;
    char *path;

    if (!pathstr)
        return NULL;

    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        if (isExecutableCommand(info, cmd))
            return cmd;
    }

    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            path = duplicateSubstring(pathstr, currPos, i);
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }
            if (isExecutableCommand(info, path))
                return path;

            if (!pathstr[i])
                break;

            currPos = i;
        }
        i++;
    }

    return NULL;
}
