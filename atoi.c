#include "shell.h"

int isInteractiveMode(info_t *info)
{
        return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

int isDelimiter(char character, char *delimiters)
{
        while (*delimiters)
                if (*delimiters++ == character)
                        return (1);
        return (0);
}

int isAlphabetic(int character)
{
        if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'))
                return (1);
        else
                return (0);
}

int customAtoi(char *string)
{
        int index, sign = 1, flag = 0, result;
        unsigned int parsedValue = 0;

        for (index = 0;  string[index] != '\0' && flag != 2; index++)
        {
                if (string[index] == '-')
                        sign *= -1;

                if (string[index] >= '0' && string[index] <= '9')    
                {
                        flag = 1;
                        parsedValue *= 10;
                        parsedValue += (string[index] - '0');        
                }
                else if (flag == 1)
                        flag = 2;
        }

        if (sign == -1)
                result = -parsedValue;
        else
                result = parsedValue;

        return (result);
}
