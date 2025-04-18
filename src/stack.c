#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack_node *create_stack_node(void *data, size_t data_size)
{
    stack_node *new_node = (stack_node *)malloc(sizeof(stack_node));
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

stack *create_stack()
{
    stack *s = (stack *)malloc(sizeof(stack));
    if (!s)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    return s;
}

int is_empty_stack(stack *s)
{
    return s->top == NULL;
}

void push_stack(stack *s, void *data, size_t data_size)
{
    stack_node *new_node = create_stack_node(data, data_size);
    new_node->next = s->top;
    s->top = new_node;
}

void *pop_stack(stack *s)
{
    if (is_empty_stack(s))
    {
        fprintf(stderr, "Stack underflow\n");
        return NULL;
    }
    stack_node *temp = s->top;
    void *data = temp->data;
    s->top = s->top->next;
    free(temp);
    return data;
}

void *peek_stack(stack *s)
{
    if (is_empty_stack(s))
    {
        fprintf(stderr, "Stack is empty\n");
        return NULL;
    }
    return s->top->data;
}

void free_stack(stack *s)
{
    while (!is_empty_stack(s))
    {
        pop_stack(s);
    }
    free(s);
}

void print_stack(stack *s, void (*print_func)(void *))
{
    stack_node *current = s->top;
    while (current)
    {
        print_func(current->data);
        current = current->next;
    }
}

stack *clone_stack(stack *s)
{
    stack *new_stack = create_stack();
    stack_node *current = s->top;
    stack_node *prev = NULL;

    while (current)
    {
        stack_node *new_node = create_stack_node(current->data, sizeof(current->data));
        if (prev)
        {
            prev->next = new_node;
        }
        else
        {
            new_stack->top = new_node;
        }
        prev = new_node;
        current = current->next;
    }
    return new_stack;
}

void reverse_stack(stack *s)
{
    stack_node *prev = NULL;
    stack_node *current = s->top;
    stack_node *next = NULL;

    while (current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    s->top = prev;
}