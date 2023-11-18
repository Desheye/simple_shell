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

int printErrorCharacter(char ch)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(2, buffer, index);
        index = 0;
    }

    if (ch != BUF_FLUSH)
        buffer[index++] = ch;

    return 1;
}

int writeCharacterToFileDescriptor(char ch, int fd)
{
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, index);
        index = 0;
    }

    if (ch != BUF_FLUSH)
        buffer[index++] = ch;

    return 1;
}

int writeStringToFileDescriptor(char *str, int fd)
{
    int count = 0;

    if (!str)
        return 0;

    while (*str)
    {
        count += writeCharacterToFileDescriptor(*str++, fd);
    }

    return count;
}

