#include "shell.h"

int displayEnvironment(info_t *info)
{
    printStringList(info->env);
    return 0;
}

char *findEnvironmentVariable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *substring;

    while (node)
    {
        substring = startsWith(node->str, name);
        if (substring && *substring)
            return substring;

        node = node->next;
    }

    return NULL;
}

int setEnvironmentVariable(info_t *info)
{
    if (info->argc != 3)
    {
        printError("_mysetenv: Incorrect number of arguments\n");
        return 1;
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

int unsetEnvironmentVariable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        printError("_myunsetenv: Too few arguments\n");
        return 1;
    }

    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return 0;
}

int populateEnvironmentList(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeEnd(&node, environ[i], 0);

    info->env = node;
    return 0;
}
