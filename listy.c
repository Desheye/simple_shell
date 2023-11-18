size_t custom_list_len(const list_t *list_head)
{
    size_t count = 0;

    while (list_head)
    {
        list_head = list_head->next;
        count++;
    }

    return count;
}

char **list_to_strings(list_t *head)
{
    list_t *node = head;
    size_t size = custom_list_len(head);
    char **strings;
    char *str;

    if (!head || !size)
        return NULL;

    strings = malloc(sizeof(char *) * (size + 1));
    if (!strings)
        return NULL;

    for (size_t i = 0; node; node = node->next, i++)
    {
        str = malloc(custom_strlen(node->str) + 1);
        if (!str)
        {
            for (size_t j = 0; j < i; j++)
                free(strings[j]);
            free(strings);
            return NULL;
        }

        str = custom_strcpy(str, node->str);
        strings[i] = str;
    }
    strings[size] = NULL;
    return strings;
}

size_t custom_print_list(const list_t *list_head)
{
    size_t count = 0;

    while (list_head)
    {
        _puts(custom_convert_number(list_head->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(list_head->str ? list_head->str : "(nil)");
        _puts("\n");
        list_head = list_head->next;
        count++;
    }

    return count;
}

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    while (node)
    {
        p = custom_starts_with(node->str, prefix);
        if (p && ((c == -1) || (*p == c)))
            return node;
        node = node->next;
    }
    return NULL;
}

ssize_t get_node_index(list_t *list_head, list_t *node)
{
    size_t index = 0;

    while (list_head)
    {
        if (list_head == node)
            return index;
        list_head = list_head->next;
        index++;
    }
    return -1;
}

