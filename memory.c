#include "shell.h"

int custom_bfree(void **pointer) {
    if (pointer && *pointer) {
        free(*pointer);
        *pointer = NULL;
        return 1;
    }
    return 0;
}

