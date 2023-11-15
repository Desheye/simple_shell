#include "shell.h"

list_t *addNodeToFront(list_t **head, const char *str, int num)
{
    list_t *newNode;

    if (!head)
        return NULL;

    newNode = malloc(sizeof(list_t));

    if (!newNode)
        return NULL;

    memset(newNode, 0, sizeof(list_t));
    newNode->num = num;

    if (str)
    {
        newNode->str = strdup(str);

        if (!newNode->str)
        {
            free(newNode);
            return NULL;
        }
    }

    newNode->next = *head;
    *head = newNode;

    return newNode;
}

list_t *addNodeToEnd(list_t **head, const char *str, int num)
{
    list_t *newNode, *node;

    if (!head)
        return NULL;

    node = *head;
    newNode = malloc(sizeof(list_t));

    if (!newNode)
        return NULL;

    memset(newNode, 0, sizeof(list_t));
    newNode->num = num;

    if (str)
    {
        newNode->str = strdup(str);

        if (!newNode->str)
        {
            free(newNode);
            return NULL;
        }
    }

    if (node)
    {
        while (node->next)
            node = node->next;

        node->next = newNode;
    }
    else
    {
        *head = newNode;
    }

    return newNode;
}

size_t printStringList(const list_t *h)
{
    size_t count = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        count++;
    }

    return count;
}

int deleteNodeAtIndex(list_t **head, unsigned int index)
{
    list_t *node, *prevNode;
    unsigned int i = 0;

    if (!head || !*head)
        return 0;

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    node = *head;

    while (node)
    {
        if (i == index)
        {
            prevNode->next = node->next;
            free(node->str);
            free(node);
            return 1;
        }

        i++;
        prevNode = node;
        node = node->next;
    }

    return 0;
}

void freeStringList(list_t **head_ptr)
{
    list_t *node, *nextNode, *head;

    if (!head_ptr || !*head_ptr)
        return;

    head = *head_ptr;
    node = head;

    while (node)
    {
        nextNode = node->next;
        free(node->str);
        free(node);
        node = nextNode;
    }

    *head_ptr = NULL;
}
