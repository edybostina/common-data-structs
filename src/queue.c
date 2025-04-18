#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/queue.h"

queue_node *create_queue_node(void *data, size_t data_size)
{
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = malloc(data_size);
    if (!new_node->data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    memcpy(new_node->data, data, data_size);
    new_node->next = NULL;
    return new_node;
}

queue *create_queue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    if (!q)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int is_empty_queue(queue *q)
{
    return q->front == NULL;
}

void enqueue(queue *q, void *data, size_t data_size)
{
    queue_node *new_node = create_queue_node(data, data_size);
    if (is_empty_queue(q))
    {
        q->front = new_node;
        q->rear = new_node;
    }
    else
    {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

void *dequeue(queue *q)
{
    if (is_empty_queue(q))
    {
        fprintf(stderr, "Queue underflow\n");
        return NULL;
    }
    queue_node *temp = q->front;
    void *data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
    {
        q->rear = NULL;
    }
    free(temp);
    return data;
}

void *peek_queue(queue *q)
{
    if (is_empty_queue(q))
    {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }
    return q->front->data;
}

void free_queue(queue *q)
{
    while (!is_empty_queue(q))
    {
        dequeue(q);
    }
    free(q);
}

void print_queue(queue *q, void (*print_func)(void *))
{
    queue_node *current = q->front;
    while (current)
    {
        print_func(current->data);
        current = current->next;
    }
}

queue *clone_queue(queue *q)
{
    if (is_empty_queue(q))
    {
        return create_queue();
    }
    queue *new_queue = create_queue();
    queue_node *current = q->front;
    while (current)
    {
        enqueue(new_queue, current->data, sizeof(current->data));
        current = current->next;
    }
    return new_queue;
}

void reverse_queue(queue *q)
{
    if (is_empty_queue(q))
    {
        return;
    }
    queue_node *prev = NULL;
    queue_node *current = q->front;
    queue_node *next = NULL;
    q->rear = q->front; // Update rear to the original front
    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    q->front = prev; // Update front to the new front
}