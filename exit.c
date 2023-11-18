#include "shell.h"

char *custom_strncpy(char *destination, char *source, int max_characters) {
    int length = 0;
    int index;
    char *result = destination;

    while (source[length] != '\0' && length < max_characters - 1) {
        destination[length] = source[length];
        length++;
    }

    if (length < max_characters) {
        index = length;
        while (index < max_characters) {
            destination[index] = '\0';
            index++;
        }
    }

    return result;
}

char *custom_strncat(char *first, char *second, int max_bytes) {
    int first_length = 0;
    int second_index = 0;
    char *result = first;

    while (first[first_length] != '\0') {
        first_length++;
    }

    while (second[second_index] != '\0' && second_index < max_bytes) {
        first[first_length] = second[second_index];
        first_length++;
        second_index++;
    }

    if (second_index < max_bytes) {
        first[first_length] = '\0';
    }

    return result;
}

char *custom_strchr(char *string, char character) {
    do {
        if (*string == character) {
            return string;
        }
    } while (*string++ != '\0');

    return NULL;
}

