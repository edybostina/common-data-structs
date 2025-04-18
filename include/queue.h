#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue_node
{
    void *data;
    struct queue_node *next;
} queue_node;

typedef struct queue
{
    queue_node *front;
    queue_node *rear;
} queue;

// Function to create a new queue node
queue_node *create_queue_node(void *data, size_t data_size);

// Function to create a new queue
queue *create_queue();

// Function to check if the queue is empty
int is_empty_queue(queue *q);

// Function to enqueue an element into the queue
void enqueue(queue *q, void *data, size_t data_size);

// Function to dequeue an element from the queue
void *dequeue(queue *q);

// Function to peek at the front element of the queue
void *peek_queue(queue *q);

// Function to free the queue
void free_queue(queue *q);

// Function to print the queue
void print_queue(queue *q, void (*print_func)(void *));

// Function to clone the queue
queue *clone_queue(queue *q);

// Function to reverse the queue
void reverse_queue(queue *q);

#endif // QUEUE_H