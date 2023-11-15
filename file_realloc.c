#include "shell.h"

char *customMemset(char *buffer, char value, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
        buffer[i] = value;
    return buffer;
}

void freeStringArray(char **stringArray)
{
    char **temp = stringArray;

    if (!stringArray)
        return;

    while (*stringArray)
        free(*stringArray++);

    free(temp);
}
void *customRealloc(void *pointer, unsigned int oldSize, unsigned int newSize)
{
    char *newPointer;

    if (!pointer)
        return malloc(newSize);

    if (!newSize)
        return free(pointer), NULL;

    if (newSize == oldSize)
        return pointer;

    newPointer = malloc(newSize);

    if (!newPointer)
        return NULL;

    oldSize = oldSize < newSize ? oldSize : newSize;

    while (oldSize--)
        newPointer[oldSize] = ((char *)pointer)[oldSize];

    free(pointer);
    return newPointer;
}

