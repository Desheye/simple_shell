#include "shell.h"

int customAtoi(char *s)
{
    int index = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++; 

    for (index = 0; s[index] != '\0'; index++)
    {
        if (s[index] >= '0' && s[index] <= '9')
        {
            result *= 10;
            result += (s[index] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }

    return result;
}

void printShellError(info_t *info, char *errorMessage)
{
    printError(info->fname);
    printError(": ");
    printLineNumber(info->line_count, STDERR_FILENO);
    printError(": ");
    printError(info->argv[0]);
    printError(": ");
    printError(errorMessage);
}

int printLineNumber(int input, int fd)
{
    int (*printChar)(char) = printCharToFD;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (fd == STDERR_FILENO)
        printChar = printCharToSTDERR;

    if (input < 0)
    {
        absoluteValue = -input;
        printChar('-');
        count++;
    }
    else
        absoluteValue = input;

    current = absoluteValue;

    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absoluteValue / i)
        {
            printChar('0' + current / i);
            count++;
        }
        current %= i;
    }

    printChar('0' + current);
    count++;

    return count;
}

char *convertNumber(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";      
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

void removeShellComments(char *buffer)
{
    int index;

    for (index = 0; buffer[index] != '\0'; index++)
        if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
        {
            buffer[index] = '\0';
            break;
        }
}
