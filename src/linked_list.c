#include <stdio.h>
#include <stdlib.h>
#include "../include/linked_list.h"

node *create_node(void *data, size_t data_size)
{
    node *new_node = (node *)malloc(sizeof(node));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    new_node->data = malloc(data_size);
    if (!new_node->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_node);
        return NULL;
    }
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    return new_node;
}

void insert_at_end(node **head, void *data, size_t data_size)
{
    node *new_node = create_node(data, data_size);
    if (!new_node)
        return;

    if (*head == NULL)
    {
        *head = new_node;
        return;
    }

    node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new_node;
}

void insert_at_beginning(node **head, void *data, size_t data_size)
{
    node *new_node = create_node(data, data_size);
    if (!new_node)
        return;

    new_node->next = *head;
    *head = new_node;
}

void insert_at_position(node **head, void *data, size_t data_size, int position)
{
    if (position == 0)
    {
        insert_at_beginning(head, data, data_size);
        return;
    }

    node *new_node = create_node(data, data_size);
    if (!new_node)
        return;

    node *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        // Position is out of bounds
        free(new_node->data);
        free(new_node);
        return;
    }

    new_node->next = temp->next;
    temp->next = new_node;
}

void insert_after(node *prev_node, void *data, size_t data_size)
{
    if (prev_node == NULL)
        return;

    node *new_node = create_node(data, data_size);
    if (!new_node)
        return;

    new_node->next = prev_node->next;
    prev_node->next = new_node;
}

void delete_from_end(node **head)
{
    if (*head == NULL)
        return;

    node *temp = *head;
    if (temp->next == NULL)
    {
        free(temp->data);
        free(temp);
        *head = NULL;
        return;
    }

    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    free(temp->next->data);
    free(temp->next);
    temp->next = NULL;
}

void delete_from_beginning(node **head)
{
    if (*head == NULL)
        return;

    node *temp = *head;
    *head = (*head)->next;
    free(temp->data);
    free(temp);
}

void delete_from_position(node **head, int position)
{
    if (*head == NULL)
        return;

    if (position == 0)
    {
        delete_from_beginning(head);
        return;
    }

    node *temp = *head;
    for (int i = 0; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL)
        return;

    node *node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    free(node_to_delete->data);
    free(node_to_delete);
}

void free_list(node **head)
{
    node *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp->data);
        free(temp);
    }
}

void sort_list(node **head, int (*compare)(void *, void *))
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    node *current, *index;
    void *temp_data;

    for (current = *head; current->next != NULL; current = current->next)
    {
        for (index = current->next; index != NULL; index = index->next)
        {
            if (compare(current->data, index->data) > 0)
            {
                temp_data = current->data;
                current->data = index->data;
                index->data = temp_data;
            }
        }
    }
}

void print_list(node *head, void (*print_func)(void *))
{
    node *temp = head;
    while (temp != NULL)
    {
        print_func(temp->data);
        temp = temp->next;
    }
}

node *find(node *head, void *data, int (*compare)(void *, void *))
{
    node *temp = head;
    while (temp != NULL)
    {
        if (compare(temp->data, data) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

node *find_at_position(node *head, int position)
{
    node *temp = head;
    for (int i = 0; i < position && temp != NULL; i++)
    {
        temp = temp->next;
    }
    return temp;
}

int length(node *head)
{
    int count = 0;
    node *temp = head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void reverse_list(node **head)
{
    node *prev = NULL;
    node *current = *head;
    node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

node *clone(node *head)
{
    if (head == NULL)
        return NULL;

    node *new_head = create_node(head->data, sizeof(head->data));
    if (!new_head)
        return NULL;

    node *current = head->next;
    node *new_current = new_head;

    while (current != NULL)
    {
        new_current->next = create_node(current->data, sizeof(current->data));
        if (!new_current->next)
            return NULL;
        new_current = new_current->next;
        current = current->next;
    }
    new_current->next = NULL;

    return new_head;
}