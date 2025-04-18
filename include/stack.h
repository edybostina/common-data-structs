#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct stack_node
{
    void *data;
    struct stack_node *next;
} stack_node;
typedef struct stack
{
    stack_node *top;
} stack;

// Function to create a new stack node
stack_node *create_stack_node(void *data, size_t data_size);

// Function to create a new stack
stack *create_stack();

// Function to check if the stack is empty
int is_empty_stack(stack *s);

// Function to push an element onto the stack
void push_stack(stack *s, void *data, size_t data_size);

// Function to pop an element from the stack
void *pop_stack(stack *s);

// Function to peek at the top element of the stack
void *peek_stack(stack *s);

// Function to free the stack
void free_stack(stack *s);

// Function to print the stack
void print_stack(stack *s, void (*print_func)(void *));

// Function to clone the stack
stack *clone_stack(stack *s);

// Function to reverse the stack
void reverse_stack(stack *s);

#endif // STACK_H