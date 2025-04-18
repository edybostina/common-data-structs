#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node
{
    void *data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

// Function to create a new tree node
tree_node *create_tree_node(void *data, size_t data_size);

// Function to insert a node into the binary tree
void insert_tree_node(tree_node **root, void *data, size_t data_size, int (*compare)(void *, void *));

// Function to search for a node in the binary tree
tree_node *search_tree_node(tree_node *root, void *data, int (*compare)(void *, void *));

// Function to delete a node from the binary tree
void delete_tree_node(tree_node **root, void *data, int (*compare)(void *, void *));

// Function to free the binary tree
void free_binary_tree(tree_node *root);

// Function to print the binary tree in-order
void print_tree_in_order(tree_node *root, void (*print_func)(void *));

// Function to print the binary tree pre-order
void print_tree_pre_order(tree_node *root, void (*print_func)(void *));

// Function to print the binary tree post-order
void print_tree_post_order(tree_node *root, void (*print_func)(void *));

// Function to find the height of the binary tree
int find_tree_height(tree_node *root);

// Function to find the size of the binary tree
int find_tree_size(tree_node *root);

// Function to find the maximum value in the binary tree
void *find_max_tree_value(tree_node *root, int (*compare)(void *, void *));

// Function to find the minimum value in the binary tree
void *find_min_tree_value(tree_node *root, int (*compare)(void *, void *));

// Function to clone the binary tree
tree_node *clone_binary_tree(tree_node *root);

// Function to check if the binary tree is balanced
int is_balanced_tree(tree_node *root);

// Function to check if the binary tree is a binary search tree
int is_bst(tree_node *root, void *min, void *max, int (*compare)(void *, void *));

// Function to find the lowest common ancestor of two nodes in the binary tree
tree_node *find_lowest_common_ancestor(tree_node *root, void *data1, void *data2, int (*compare)(void *, void *));

// Function to find the diameter of the binary tree
int find_tree_diameter(tree_node *root);

// Function to find the level of a node in the binary tree
int find_node_level(tree_node *root, void *data, int level, int (*compare)(void *, void *));

// Function to find the path from root to a given node in the binary tree
void find_path_to_node(tree_node *root, void *data, int (*compare)(void *, void *), char *path, int *path_index);

// Function to print the path from root to a given node in the binary tree
void print_path_to_node(tree_node *root, void *data, int (*compare)(void *, void *));

// Function to check if the binary tree is a complete binary tree
int is_complete_tree(tree_node *root);

// Function to check if the binary tree is a full binary tree
int is_full_tree(tree_node *root);

// Function to check if the binary tree is a perfect binary tree
int is_perfect_tree(tree_node *root);

#endif // BINARY_TREE_H