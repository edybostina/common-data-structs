#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    void *data;
    struct node *next;

} node;

// Creates a new node with the given data and size.
node *create_node(void *data, size_t data_size);

// Inserts a new node at the end of the linked list.
void insert_at_end(node **head, void *data, size_t data_size);

// Inserts a new node at the beginning of the linked list.
void insert_at_beginning(node **head, void *data, size_t data_size);

// Inserts a new node at a specific position in the linked list.
void insert_at_position(node **head, void *data, size_t data_size, int position);

// Inserts a new node after a given node in the linked list.
void insert_after(node *prev_node, void *data, size_t data_size);

// Deletes the last node from the linked list.
void delete_from_end(node **head);

// Deletes the first node from the linked list.
void delete_from_beginning(node **head);

// Deletes a node from a specific position in the linked list.
void delete_from_position(node **head, int position);

// Prints the linked list using a print function.
void print_list(node *head, void (*print_func)(void *));

// Sorts the linked list using a comparison function.
void sort_list(node **head, int (*compare)(void *, void *));

// Searches for a node in the linked list using a comparison function.
node *find(node *head, void *data, int (*compare)(void *, void *));

// Searches for a node in the linked list at a specific position.
node *find_at_position(node *head, int position);

// Clones the linked list.
node *clone(node *head);

// Returns the length of the linked list.
int length(node *head);

// Reverses the linked list.
void reverse_list(node **head);

// Frees the entire linked list.
void free_list(node **head);

#endif // LINKED_LIST_H