#include "shell.h"

char **splitString(char *inputString, char *delimiterString)
{
        int i, j, k, m, numWords = 0;
        char **result;

        if (inputString == NULL || inputString[0] == 0)
                return NULL;

        if (!delimiterString)
                delimiterString = " ";

        for (i = 0; inputString[i] != '\0'; i++)
                if (!isDelimiter(inputString[i], delimiterString) && (isDelimiter(inputString[i + 1], delimiterString) || !inputString[i + 1]))
                        numWords++;

        if (numWords == 0)
                return NULL;

        result = malloc((1 + numWords) * sizeof(char *));
        if (!result)
                return NULL;

        for (i = 0, j = 0; j < numWords; j++)
        {
                while (isDelimiter(inputString[i], delimiterString))
                        i++;

                k = 0;
                while (!isDelimiter(inputString[i + k], delimiterString) && inputString[i + k])
                        k++;

                result[j] = malloc((k + 1) * sizeof(char));
                if (!result[j])
                {
                        for (k = 0; k < j; k++)
                                free(result[k]);
                        free(result);
                        return NULL;
                }

                for (m = 0; m < k; m++)
                        result[j][m] = inputString[i++];
                result[j][m] = 0;
        }

        result[j] = NULL;
        return result;
}

char **splitStringByChar(char *inputString, char delimiterChar)
{
        int i, j, k, m, numWords = 0;
        char **result;

        if (inputString == NULL || inputString[0] == 0)
                return NULL;

        for (i = 0; inputString[i] != '\0'; i++)
                if ((inputString[i] != delimiterChar && inputString[i + 1] == delimiterChar) ||
                        (inputString[i] != delimiterChar && !inputString[i + 1]) || inputString[i + 1] == delimiterChar)
                        numWords++;

        if (numWords == 0)
                return NULL;

        result = malloc((1 + numWords) * sizeof(char *));
        if (!result)
                return NULL;

        for (i = 0, j = 0; j < numWords; j++)
        {
                while (inputString[i] == delimiterChar && inputString[i] != delimiterChar)
                        i++;

                k = 0;
                while (inputString[i + k] != delimiterChar && inputString[i + k] && inputString[i + k] != delimiterChar)
                        k++;

                result[j] = malloc((k + 1) * sizeof(char));
                if (!result[j])
                {
                        for (k = 0; k < j; k++)
                                free(result[k]);
                        free(result);
                        return NULL;
                }

                for (m = 0; m < k; m++)
                        result[j][m] = inputString[i++];
                result[j][m] = 0;
        }

        result[j] = NULL;
        return result;
}
