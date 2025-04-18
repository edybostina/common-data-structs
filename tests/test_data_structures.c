#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data_structures.h"

typedef struct myStruct
{
    int a;
    char b[20];
} myStruct;

void print_myStruct(void *data)
{
    myStruct *s = (myStruct *)data;
    printf("a: %d, b: %s\n", s->a, s->b);
}

int compare_myStruct(void *data1, void *data2)
{
    myStruct *s1 = (myStruct *)data1;
    myStruct *s2 = (myStruct *)data2;
    if (s1->a < s2->a)
        return -1;
    else if (s1->a > s2->a)
        return 1;
    else
        return 0;
}

void test_linked_list()
{
    node *linked_list = NULL;
    myStruct data1 = {3, "Hello"};
    myStruct data2 = {1, "World"};
    myStruct data3 = {5, "!"};
    myStruct data4 = {9, "Goodbye"};
    myStruct data5 = {9, "!"};

    insert_at_end(&linked_list, &data1, sizeof(myStruct));
    insert_at_end(&linked_list, &data2, sizeof(myStruct));
    insert_at_end(&linked_list, &data3, sizeof(myStruct));
    insert_at_end(&linked_list, &data4, sizeof(myStruct));
    insert_at_end(&linked_list, &data5, sizeof(myStruct));

    printf("Original list:\n");
    print_list(linked_list, print_myStruct);
    printf("\n");

    printf("Length of list: %d\n", length(linked_list));
    printf("\n");

    printf("Finding element at position 2:\n");
    node *found_node = find_at_position(linked_list, 2);
    if (found_node)
    {
        printf("Element found: ");
        print_myStruct(found_node->data);
    }
    else
    {
        printf("Element not found\n");
    }
    printf("\n");

    printf("Reversing list:\n");
    reverse_list(&linked_list);
    print_list(linked_list, print_myStruct);
    printf("\n");

    printf("Sorting list:\n");
    sort_list(&linked_list, compare_myStruct);
    print_list(linked_list, print_myStruct);
    printf("\n");

    // Add more tests here...

    free_list(&linked_list);
}

void test_stack()
{
    stack *s = create_stack();
    myStruct data1 = {3, "Stack"};
    myStruct data2 = {1, "Overflow"};
    myStruct data3 = {5, "Rulz"};
    myStruct data4 = {9, "stackoverflow.com"};

    push_stack(s, &data1, sizeof(myStruct));
    push_stack(s, &data2, sizeof(myStruct));
    push_stack(s, &data3, sizeof(myStruct));
    push_stack(s, &data4, sizeof(myStruct));

    printf("Stack after pushing elements:\n");
    print_stack(s, print_myStruct);
    printf("\n");

    printf("Popping element: ");
    myStruct *popped_data = (myStruct *)pop_stack(s);
    print_myStruct(popped_data);
    free(popped_data);
    printf("\n");

    printf("Stack after popping element:\n");
    print_stack(s, print_myStruct);
    printf("\n");

    // Add more tests here...

    free_stack(s);
}

void test_queue()
{
    queue *q = create_queue();
    myStruct data1 = {3, "This"};
    myStruct data2 = {1, "Queue"};
    myStruct data3 = {5, "Rocks"};
    myStruct data4 = {9, "Goodbye"};

    enqueue(q, &data1, sizeof(myStruct));
    enqueue(q, &data2, sizeof(myStruct));
    enqueue(q, &data3, sizeof(myStruct));
    enqueue(q, &data4, sizeof(myStruct));

    printf("Queue after enqueuing elements:\n");
    print_queue(q, print_myStruct);
    printf("\n");

    printf("Dequeuing element: ");
    myStruct *dequeued_data = (myStruct *)dequeue(q);
    print_myStruct(dequeued_data);
    free(dequeued_data);
    printf("\n");

    printf("Queue after dequeuing element:\n");
    print_queue(q, print_myStruct);
    printf("\n");

    // Add more tests here...

    free_queue(q);
}

void test_binary_tree()
{
    myStruct data1 = {5, "Root"};
    tree_node *tree = create_tree_node(&data1, sizeof(myStruct));
    myStruct data2 = {3, "Left"};
    myStruct data3 = {7, "Right"};
    myStruct data4 = {2, "Left-Left"};
    myStruct data5 = {4, "Left-Right"};
    myStruct data6 = {6, "Right-Left"};
    myStruct data7 = {8, "Right-Right"};

    printf("Inserting elements into the binary tree:\n");
    insert_tree_node(&tree, &data2, sizeof(myStruct), compare_myStruct);
    insert_tree_node(&tree, &data3, sizeof(myStruct), compare_myStruct);
    insert_tree_node(&tree, &data4, sizeof(myStruct), compare_myStruct);
    insert_tree_node(&tree, &data5, sizeof(myStruct), compare_myStruct);
    insert_tree_node(&tree, &data6, sizeof(myStruct), compare_myStruct);
    insert_tree_node(&tree, &data7, sizeof(myStruct), compare_myStruct);

    printf("Binary tree in-order traversal:\n");
    print_tree_in_order(tree, print_myStruct);
    printf("\n");

    printf("Binary tree pre-order traversal:\n");
    print_tree_pre_order(tree, print_myStruct);
    printf("\n");

    printf("Binary tree post-order traversal:\n");
    print_tree_post_order(tree, print_myStruct);
    printf("\n");

    printf("Searching for element with key 4:\n");
    tree_node *found_node = search_tree_node(tree, &data5, compare_myStruct);
    if (found_node)
    {
        printf("Element found: ");
        print_myStruct(found_node->data);
    }
    else
    {
        printf("Element not found\n");
    }
    printf("\n");

    printf("Deleting element with key 3:\n");
    delete_tree_node(&tree, &data2, compare_myStruct);
    printf("Binary tree in-order traversal after deletion:\n");
    print_tree_in_order(tree, print_myStruct);
    printf("\n");

    free_binary_tree(tree);
}

int main()
{
    printf("Hello, welcome to the data structures test program!\n");
    printf("What would you like to test?\n");
    printf("1. Linked List\n");
    printf("2. Stack\n");
    printf("3. Queue\n");
    printf("4. Binary Tree\n");
    printf("5. Hash Table\n");
    printf("6. Heap\n");
    printf("7. All\n");
    printf("8. Exit\n");
    int choice;
    while (1)
    {
        printf("Enter your choice: (enter 8 to terminate)\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            test_linked_list();
            break;
        case 2:
            test_stack();
            break;
        case 3:
            test_queue();
            break;
        case 4:
            test_binary_tree();
            break;
        case 5:
            // test_hash_table();
            break;
        case 6:
            // test_heap();
            break;
        case 7:
            test_linked_list();
            test_stack();
            // test_queue();
            // test_binary_tree();
            // test_hash_table();
            // test_heap();
            break;
        case 8:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice, please try again.\n");
        }
    }
}