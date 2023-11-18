int custom_strlen(char *s)
{
    int length = 0;

    if (!s)
        return 0;

    while (*s++)
        length++;

    return length;
}

char *custom_starts_with(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return NULL;

    return (char *)haystack;
}

char *custom_strcat(char *dest, char *src)
{
    char *ptr = dest;

    while (*dest)
        dest++;

    while (*src)
        *dest++ = *src++;

    *dest = *src;
    return ptr;
}

int custom_strcmp(char *str1, char *str2)
{
    while (*str1 && *str2) {
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

