#include <stdio.h>
#include <stdlib.h>
#include "../include/binary_tree.h"
#include "../include/queue.h"

tree_node *create_tree_node(void *data, size_t data_size)
{
    tree_node *new_node = (tree_node *)malloc(sizeof(tree_node));
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
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert_tree_node(tree_node **root, void *data, size_t data_size, int (*compare)(void *, void *))
{
    if (*root == NULL)
    {
        *root = create_tree_node(data, data_size);
        return;
    }
    if (compare(data, (*root)->data) < 0)
    {
        insert_tree_node(&(*root)->left, data, data_size, compare);
    }
    else
    {
        insert_tree_node(&(*root)->right, data, data_size, compare);
    }
}

tree_node *search_tree_node(tree_node *root, void *data, int (*compare)(void *, void *))
{
    if (root == NULL || compare(data, root->data) == 0)
    {
        return root;
    }
    if (compare(data, root->data) < 0)
    {
        return search_tree_node(root->left, data, compare);
    }
    return search_tree_node(root->right, data, compare);
}

void delete_tree_node(tree_node **root, void *data, int (*compare)(void *, void *))
{
    if (*root == NULL)
    {
        return;
    }
    if (compare(data, (*root)->data) < 0)
    {
        delete_tree_node(&(*root)->left, data, compare);
    }
    else if (compare(data, (*root)->data) > 0)
    {
        delete_tree_node(&(*root)->right, data, compare);
    }
    else
    {
        tree_node *temp = *root;
        if ((*root)->left == NULL)
        {
            *root = (*root)->right;
        }
        else if ((*root)->right == NULL)
        {
            *root = (*root)->left;
        }
        else
        {
            tree_node *successor = (*root)->right;
            while (successor->left != NULL)
            {
                successor = successor->left;
            }
            free((*root)->data);
            (*root)->data = successor->data;
            delete_tree_node(&(*root)->right, successor->data, compare);
            return;
        }
        free(temp->data);
        free(temp);
    }
}

void free_binary_tree(tree_node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_binary_tree(root->left);
    free_binary_tree(root->right);
    free(root->data);
    free(root);
}

void print_tree_in_order(tree_node *root, void (*print_func)(void *))
{
    if (root == NULL)
    {
        return;
    }
    print_tree_in_order(root->left, print_func);
    print_func(root->data);
    print_tree_in_order(root->right, print_func);
}

void print_tree_pre_order(tree_node *root, void (*print_func)(void *))
{
    if (root == NULL)
    {
        return;
    }
    print_func(root->data);
    print_tree_pre_order(root->left, print_func);
    print_tree_pre_order(root->right, print_func);
}

void print_tree_post_order(tree_node *root, void (*print_func)(void *))
{
    if (root == NULL)
    {
        return;
    }
    print_tree_post_order(root->left, print_func);
    print_tree_post_order(root->right, print_func);
    print_func(root->data);
}

int find_tree_height(tree_node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int left_height = find_tree_height(root->left);
    int right_height = find_tree_height(root->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

int find_tree_size(tree_node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return find_tree_size(root->left) + find_tree_size(root->right) + 1;
}

void *find_max_tree_value(tree_node *root, int (*compare)(void *, void *))
{
    if (root == NULL)
    {
        return NULL;
    }
    tree_node *current = root;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current->data;
}

void *find_min_tree_value(tree_node *root, int (*compare)(void *, void *))
{
    if (root == NULL)
    {
        return NULL;
    }
    tree_node *current = root;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current->data;
}

tree_node *clone_binary_tree(tree_node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    tree_node *new_node = create_tree_node(root->data, sizeof(root->data));
    new_node->left = clone_binary_tree(root->left);
    new_node->right = clone_binary_tree(root->right);
    return new_node;
}

int abs(int x)
{
    return (x < 0) ? -x : x;
}

int is_balanced_tree(tree_node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    int left_height = find_tree_height(root->left);
    int right_height = find_tree_height(root->right);
    if (abs(left_height - right_height) > 1)
    {
        return 0;
    }
    return is_balanced_tree(root->left) && is_balanced_tree(root->right);
}

int is_bst(tree_node *root, void *min, void *max, int (*compare)(void *, void *))
{
    if (root == NULL)
    {
        return 1;
    }
    if ((min != NULL && compare(root->data, min) <= 0) || (max != NULL && compare(root->data, max) >= 0))
    {
        return 0;
    }
    return is_bst(root->left, min, root->data, compare) && is_bst(root->right, root->data, max, compare);
}

tree_node *find_lowest_common_ancestor(tree_node *root, void *data1, void *data2, int (*compare)(void *, void *))
{
    if (root == NULL)
    {
        return NULL;
    }
    if (compare(data1, root->data) < 0 && compare(data2, root->data) < 0)
    {
        return find_lowest_common_ancestor(root->left, data1, data2, compare);
    }
    if (compare(data1, root->data) > 0 && compare(data2, root->data) > 0)
    {
        return find_lowest_common_ancestor(root->right, data1, data2, compare);
    }
    return root;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int find_tree_diameter(tree_node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int left_height = find_tree_height(root->left);
    int right_height = find_tree_height(root->right);
    int left_diameter = find_tree_diameter(root->left);
    int right_diameter = find_tree_diameter(root->right);
    return max(left_height + right_height + 1, max(left_diameter, right_diameter));
}

int find_node_level(tree_node *root, void *data, int level, int (*compare)(void *, void *))
{
    if (root == NULL)
    {
        return -1;
    }
    if (compare(data, root->data) == 0)
    {
        return level;
    }
    int left_level = find_node_level(root->left, data, level + 1, compare);
    if (left_level != -1)
    {
        return left_level;
    }
    return find_node_level(root->right, data, level + 1, compare);
}

int is_complete_tree(tree_node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    queue *q = create_queue();
    enqueue(q, root, sizeof(tree_node *));
    int end = 0;
    while (!is_empty_queue(q))
    {
        tree_node *current = (tree_node *)dequeue(q);
        if (current == NULL)
        {
            end = 1;
        }
        else
        {
            if (end)
            {
                free_queue(q);
                return 0;
            }
            enqueue(q, current->left, sizeof(tree_node *));
            enqueue(q, current->right, sizeof(tree_node *));
        }
    }
    free_queue(q);
    return 1;
}

int is_full_tree(tree_node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    if (root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    if (root->left != NULL && root->right != NULL)
    {
        return is_full_tree(root->left) && is_full_tree(root->right);
    }
    return 0;
}

int is_perfect_tree(tree_node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    int left_height = find_tree_height(root->left);
    int right_height = find_tree_height(root->right);
    if (left_height != right_height)
    {
        return 0;
    }
    return is_perfect_tree(root->left) && is_perfect_tree(root->right);
}
