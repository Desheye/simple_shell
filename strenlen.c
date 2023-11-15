#include "shell.h"

int stringLength(char *str)
{
        int length = 0;

        if (!str)
                return 0;

        while (*str++)
                length++;
        return length;
}

int stringCompare(char *str1, char *str2)
{
        while (*str1 && *str2)
        {
                if (*str1 != *str2)
                        return (*str1 - *str2);
                str1++;
                str2++;
        }
        if (*str1 == *str2)
                return 0;
        else
                return (*str1 < *str2 ? -1 : 1);
}

char *stringStartsWith(const char *haystack, const char *needle)
{
        while (*needle)
                if (*needle++ != *haystack++)
                        return NULL;
        return (char *)haystack;
}

char *stringConcatenate(char *destination, char *source)
{
        char *result = destination;

        while (*destination)
                destination++;
        while (*source)
                *destination++ = *source++;
        *destination = *source;
        return result;
}
