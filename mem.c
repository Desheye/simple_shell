#include "shell.h"

int freeAndNull(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }

    return 0;
}
