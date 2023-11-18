#include "shell.h"

int displayEnvironment(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

char *getEnvironmentVariable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = starts_with(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }
    return NULL;
}

int setEnvironmentVariable(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
        return 0;

    return 1;
}

int unsetEnvironmentVariable(info_t *info)
{
    int j;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (j = 1; j < info->argc; j++)
        _unsetenv(info, info->argv[j]);

    return 0;
}

int populateEnvironmentList(info_t *info)
{
    list_t *node = NULL;
    size_t index;

    for (index = 0; environ[index]; index++)
        add_node_end(&node, environ[index], 0);

    info->env = node;
    return 0;
}

