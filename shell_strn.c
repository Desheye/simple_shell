#include "shell.h"

char *custom_strcpy(char *destination, char *source) {
    int index = 0;

    if (destination == source || source == 0)
        return destination;

    while (source[index]) {
        destination[index] = source[index];
        index++;
    }

    destination[index] = 0;
    return destination;
}

char *custom_strdup(const char *input_str) {
    int length = 0;
    char *result;

    if (input_str == NULL)
        return NULL;

    while (*input_str++)
        length++;

    result = malloc(sizeof(char) * (length + 1));

    if (!result)
        return NULL;

    for (length++; length--;)
        result[length] = *--input_str;

    return result;
}

void custom_puts(char *input_str) {
    int index = 0;

    if (!input_str)
        return;

    while (input_str[index] != '\0') {
        custom_putchar(input_str[index]);
        index++;
    }
}

int custom_putchar(char character) {
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || index >= WRITE_BUF_SIZE) {
        write(1, buffer, index);
        index = 0;
    }

    if (character != BUF_FLUSH)
        buffer[index++] = character;

    return 1;
}

