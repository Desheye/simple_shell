#include "shell.h"

int displayHistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

int unsetAlias(info_t *info, char *str)
{
    char *equals, delimiter;
    int result;

    equals = _strchr(str, '=');
    if (!equals)
        return 1;

    delimiter = *equals;
    *equals = 0;
    result = delete_node_at_index(&(info->alias),
                                   get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *equals = delimiter;

    return result;
}

int setAlias(info_t *info, char *str1)
{
    char *equals;

    equals = _strchr(str1, '=');
    if (!equals)
        return 1;

    if (!*++equals)
        return unsetAlias(info, str1);

    unsetAlias(info, str1);
    return add_node_end(&(info->alias), str1, 0) == NULL;
}

int printAlias(list_t *node)
{
    char *equals = NULL, *alias = NULL;

    if (node)
    {
        equals = _strchr(node->str, '=');
        for (alias = node->str; alias <= equals; alias++)
            _putchar(*alias);
        _putchar('\'');
        _puts(equals + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

int manageAlias(info_t *info)
{
    int index = 0;
    char *equals = NULL;
    list_t *aliasNode = NULL;

    if (info->argc == 1)
    {
        aliasNode = info->alias;
        while (aliasNode)
        {
            printAlias(aliasNode);
            aliasNode = aliasNode->next;
        }
        return 0;
    }

    for (index = 1; info->argv[index]; index++)
    {
        equals = _strchr(info->argv[index], '=');
        if (equals)
            setAlias(info, info->argv[index]);
        else
            printAlias(node_starts_with(info->alias, info->argv[index], '='));
    }

    return 0;
}

