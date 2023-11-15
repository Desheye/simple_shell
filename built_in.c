#include "shell.h"

int displayHistory(info_t *info)
{
    printList(info->history);
    return 0;
}

int unsetAlias(info_t *info, char *aliasString)
{
    char *equalsPosition, savedChar;
    int result;

    equalsPosition = _strchr(aliasString, '=');
    if (!equalsPosition)
        return 1;

    savedChar = *equalsPosition;
    *equalsPosition = '\0';

    result = deleteNodeAtIndex(&(info->alias),
        getNodeIndex(info->alias, nodeStartsWith(info->alias, aliasString, -1)));

    *equalsPosition = savedChar;

    return result;
}

int setAlias(info_t *info, char *aliasString)
{
    char *equalsPosition;

    equalsPosition = _strchr(aliasString, '=');
    if (!equalsPosition)
        return 1;

    if (!*++equalsPosition)
        return unsetAlias(info, aliasString);

    unsetAlias(info, aliasString);
    return (addNodeEnd(&(info->alias), aliasString, 0) == NULL);     
}

int printAlias(list_t *node)
{
    char *equalsPosition = NULL, *alias = NULL;

    if (node)
    {
        equalsPosition = _strchr(node->str, '=');
        for (alias = node->str; alias <= equalsPosition; alias++)    
            _putchar(*alias);
        _putchar('\'');
        _puts(equalsPosition + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

int handleAlias(info_t *info)
{
    int i = 0;
    char *equalsPosition = NULL;
    list_t *node = NULL;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            printAlias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equalsPosition = _strchr(info->argv[i], '=');
        if (equalsPosition)
            setAlias(info, info->argv[i]);
        else
            printAlias(nodeStartsWith(info->alias, info->argv[i], '='));
    }

    return 0;
}
