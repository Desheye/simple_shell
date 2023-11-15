#include "shell.h"

void initializeInfo(info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

void populateInfo(info_t *info, char **arguments)
{
    int i = 0;

    info->fname = arguments[0];

    if (info->arg)
    {
        info->argv = splitString(info->arg, " \t");

        if (!info->argv)
        {
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = duplicateString(info->arg);
                info->argv[1] = NULL;
            }
        }

        for (i = 0; info->argv && info->argv[i]; i++)
            ;

        info->argc = i;

        replaceAlias(info);
        replaceVariables(info);
    }
}
void releaseInfo(info_t *info, int freeAll)
{
    freeStringArray(info->argv);
    info->argv = NULL;
    info->path = NULL;

    if (freeAll)
    {
        if (!info->cmd_buffer)
            free(info->arg);

        if (info->env)
            freeList(&(info->env));

        if (info->history)
            freeList(&(info->history));

        if (info->alias)
            freeList(&(info->alias));

        freeStringArray(info->environ);
        info->environ = NULL;

        freeBuffer((void **)info->cmd_buffer);

        if (info->readfd > 2)
            close(info->readfd);

        printCharToFD(BUFFER_FLUSH);
    }
}
