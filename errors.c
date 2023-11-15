#include "shell.h"

void printErrorString(char *str)
{
    int index = 0;

    if (!str)
        return;

    while (str[index] != '\0')
    {
        printErrorCharacter(str[index]);
        index++;
    }
}

int printErrorCharacter(char c)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
    {
        write(2, buffer, index);
        index = 0;
    }

    if (c != BUFFER_FLUSH)
        buffer[index++] = c;

    return 1;
}

int writeToFD(char c, int fileDescriptor)
{
    static int index;
    static char buffer[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
    {
        write(fileDescriptor, buffer, index);
        index = 0;
    }

    if (c != BUFFER_FLUSH)
        buffer[index++] = c;

    return 1;
}

int writeStringToFD(char *str, int fileDescriptor)
{
    int index = 0;

    if (!str)
        return 0;

    while (*str)
    {
        index += writeToFD(*str++, fileDescriptor);
    }

    return index;
}
