#include "shell.h"

int convertStringToInteger(char *str)
{
	int index = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
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
	_eputs(info->fname);
	_eputs(": ");
	printLineNumber(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errorMessage);
}

int printLineNumber(int lineNumber, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absValue, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (lineNumber < 0)
	{
		absValue = -lineNumber;
		__putchar('-');
		count++;
	}
	else
		absValue = lineNumber;

	current = absValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absValue / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return count;
}

char *convertNumberToString(long int number, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long value  = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		value = -number;
		sign = '-';
	}

	digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = digits[value % base];
		value /= base;
	} while (value != 0);

	if (sign)
		*--ptr = sign;
	return ptr;
}

void removeComments(char *buffer)
{
	int index;

	for (index = 0; buffer[index] != '\0'; index++)
		if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
		{
			buffer[index] = '\0';
			break;
		}
}

