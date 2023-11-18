#include "shell.h"

char **custom_strtow(char *input_str, char *delimiter_str) {
    int index, length, word_index, char_index, num_words = 0;
    char **result;

    if (input_str == NULL || input_str[0] == 0)
        return NULL;

    if (!delimiter_str)
        delimiter_str = " ";

    for (index = 0; input_str[index] != '\0'; index++)
        if (!is_delim(input_str[index], delimiter_str) &&
            (is_delim(input_str[index + 1], delimiter_str) || !input_str[index + 1]))
            num_words++;

    if (num_words == 0)
        return NULL;

    result = malloc((1 + num_words) * sizeof(char *));
    if (!result)
        return NULL;

    for (index = 0, word_index = 0; word_index < num_words; word_index++) {
        while (is_delim(input_str[index], delimiter_str))
            index++;

        length = 0;
        while (!is_delim(input_str[index + length], delimiter_str) && input_str[index + length])
            length++;

        result[word_index] = malloc((length + 1) * sizeof(char));
        if (!result[word_index]) {
            for (length = 0; length < word_index; length++)
                free(result[length]);
            free(result);
            return NULL;
        }

        for (char_index = 0; char_index < length; char_index++)
            result[word_index][char_index] = input_str[index++];

        result[word_index][char_index] = 0;
    }

    result[word_index] = NULL;
    return result;
}

char **custom_strtow2(char *input_str, char delimiter) {
    int index, length, word_index, char_index, num_words = 0;
    char **result;

    if (input_str == NULL || input_str[0] == 0)
        return NULL;

    for (index = 0; input_str[index] != '\0'; index++)
        if ((input_str[index] != delimiter && input_str[index + 1] == delimiter) ||
            (input_str[index] != delimiter && !input_str[index + 1]) || input_str[index + 1] == delimiter)
            num_words++;

    if (num_words == 0)
        return NULL;

    result = malloc((1 + num_words) * sizeof(char *));
    if (!result)
        return NULL;

    for (index = 0, word_index = 0; word_index < num_words; word_index++) {
        while (input_str[index] == delimiter && input_str[index] != delimiter)
            index++;

        length = 0;
        while (input_str[index + length] != delimiter && input_str[index + length] && input_str[index + length] != delimiter)
            length++;

        result[word_index] = malloc((length + 1) * sizeof(char));
        if (!result[word_index]) {
            for (length = 0; length < word_index; length++)
                free(result[length]);
            free(result);
            return NULL;
        }

        for (char_index = 0; char_index < length; char_index++)
            result[word_index][char_index] = input_str[index++];

        result[word_index][char_index] = 0;
    }

    result[word_index] = NULL;
    return result;
}

