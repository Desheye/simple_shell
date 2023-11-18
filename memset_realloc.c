#include "shell.h"

char *custom_memset(char *memory, char byte, unsigned int size) {
    unsigned int index;

    for (index = 0; index < size; index++)
        memory[index] = byte;

    return memory;
}

void custom_ffree(char **string_array) {
    char **temp = string_array;

    if (!string_array)
        return;

    while (*string_array)
        free(*string_array++);

    free(temp);
}

void *custom_realloc(void *pointer, unsigned int old_size, unsigned int new_size) {
    char *new_pointer;

    if (!pointer)
        return malloc(new_size);

    if (!new_size)
        return free(pointer), NULL;

    if (new_size == old_size)
        return pointer;

    new_pointer = malloc(new_size);

    if (!new_pointer)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;

    while (old_size--)
        new_pointer[old_size] = ((char *)pointer)[old_size];

    free(pointer);
    return new_pointer;
}

