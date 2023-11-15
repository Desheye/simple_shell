#include "shell.h"

char *copyString(char *destination, char *source)
{
        int index = 0;

        if (destination == source || source == NULL)
                return destination;

        while (source[index])
        {
                destination[index] = source[index];
                index++;
        }
        destination[index] = '\0';
        return destination;
}

char *duplicateString(const char *str)
{
        int length = 0;
        char *result;

        if (str == NULL)
                return NULL;

        while (*str++)
                length++;

        result = malloc(sizeof(char) * (length + 1));
        if (!result)
                return NULL;

        for (length++; length--;)
                result[length] = *--str;

        return result;
}

void printString(char *str)
{
        int index = 0;

        if (!str)
                return;

        while (str[index] != '\0')
        {
                writeCharacter(str[index]);
                index++;
        }
}

int writeCharacter(char character)
{
        static int bufferIndex;
        static char buffer[WRITE_BUFFER_SIZE];

        if (character == BUFFER_FLUSH || bufferIndex >= WRITE_BUFFER_SIZE)
        {
                write(1, buffer, bufferIndex);
                bufferIndex = 0;
        }
        if (character != BUFFER_FLUSH)
                buffer[bufferIndex++] = character;
        return 1;
}
