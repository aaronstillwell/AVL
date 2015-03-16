#include <stdlib.h>
#include <string.h>

#include "AVL_Tree.h"
#include "util.h"

AVL_Node* AVL_Node_create(char* key)
{
    AVL_Node* node = malloc(sizeof(AVL_Node));
    node->key = malloc(strlen(key));
    strcpy(node->key, key);
    node->count = 1;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVL_Tree* AVL_Tree_create()
{
    AVL_Tree* tree = malloc(sizeof(AVL_Tree));
    tree->root = NULL;
    return tree;
}

AVL_Node* AVL_search(AVL_Tree* tree, char* key)
{
    AVL_Node* node = tree->root;

    while(node != NULL) {
        if (strcmp(key, node->key) == 0) {
            return node;
        }

        if (strcmp(node->key, key) > 0) {
            node = node->right;
        }else if (strcmp(node->key, key) < 0) {
            node = node->left;
        }
    }
    return NULL;
}

AVL_Node* AVL_rotate_left(AVL_Node* node)
{
    AVL_Node* right = node->right;
    node->right = right->left;
    right->left = node;

    node->height = max(AVL_node_height(node->left), AVL_node_height(node->right)) + 1;
    right->height = max(AVL_node_height(right->left), AVL_node_height(right->right)) + 1;

    return right;
}

AVL_Node* AVL_rotate_right(AVL_Node* node)
{
    AVL_Node* left = node->left;
    node->left = left->right;
    left->right = node;

    node->height = max(AVL_node_height(node->left), AVL_node_height(node->right)) + 1;
    left->height = max(AVL_node_height(left->left), AVL_node_height(left->right)) + 1;

    return left;
}

AVL_Node* AVL_rotate_left_right(AVL_Node* node)
{
    AVL_Node* new_root = AVL_rotate_left(node);
    return AVL_rotate_right(new_root);
}

AVL_Node* AVL_rotate_right_left(AVL_Node* node)
{
    AVL_Node* new_root = AVL_rotate_right(node);
    return AVL_rotate_left(new_root);
}

AVL_Node* AVL_rebalance(AVL_Node* root)
{
    int bf;
    root->height = max(AVL_node_height(root->left), AVL_node_height(root->right)) + 1;

    bf = AVL_node_height(root->left) - AVL_node_height(root->right);

    if (bf > 1) {
        if (AVL_node_height(root->left->left) - AVL_node_height(root->left->right) > 0) {
            return AVL_rotate_right(root);
        }else{
            return AVL_rotate_right_left(root);
        }
    }else if (bf < -1) {
        if (AVL_node_height(root->right->left) - AVL_node_height(root->right->right) < 0) {
            return AVL_rotate_left(root);
        }else{
            return AVL_rotate_left_right(root);
        }
    }

    return root;
}

void AVL_insert(AVL_Tree* tree, char* key)
{
    AVL_Node* node = AVL_Node_create(key);
    if (tree->root == NULL) {
        tree->root = node;
        tree->root->height = 0;
    }else{
        tree->root = AVL_insert_node(tree->root, node);
    }
}

AVL_Node* AVL_insert_node(AVL_Node* root, AVL_Node* node)
{
    int comparison = strcmp(root->key, node->key);
    if (comparison < 0) {
        if (root->left == NULL) {
            root->left = node;
        }else{
            root->left = AVL_insert_node(root->left, node);
        }
    }else if (comparison > 0) {
        if (root->right == NULL) {
            root->right = node;
        }else{
            root->right = AVL_insert_node(root->right, node);
        }
    }

    return AVL_rebalance(root);
}

int AVL_node_height(AVL_Node* node) {
    if (node == NULL) {
        return -1;
    }else{
        return node->height;
    }
}

void AVL_remove(AVL_Tree* tree, char* key)
{
    if (strcmp(tree->root->key, key) == 0) {
        if (tree->root->left == NULL && tree->root->right == NULL) {
            tree->root = NULL;
        }else if (tree->root->left == NULL && tree->root->right != NULL) {
            tree->root = tree->root->right;
        }else if (tree->root->left != NULL && tree->root->right == NULL) {
            tree->root = tree->root->right;
        }else{
            AVL_Node* largest_parent;
            AVL_Node* largest = tree->root->left;
            while (largest->right != NULL) {
                largest = largest->right;
            }
            largest_parent = AVL_find_parent(tree, largest);
            largest_parent->right = NULL;
            free(tree->root->key);
            tree->root->key = largest->key;
            free(largest);
        }
    }else{
        AVL_remove_node(tree, tree->root, key);
    }
}

void AVL_remove_node(AVL_Tree* tree, AVL_Node* node, char* key)
{
    int comparison = strcmp(node->key, key);
    if (comparison == 0) {
        AVL_Node* parent = AVL_find_parent(tree, node);

        if (node->left == NULL && node->right == NULL) {
            if (strcmp(parent->key, node->key) < 0) {
                parent->left = NULL;
            }else{
                parent->right = NULL;
            }
        }else if (node->left == NULL && node->right != NULL) {
            if (strcmp(parent->key, node->key) < 0) {
                parent->left = node->right;
            }else{
                parent->right = node->right;
            }
        }else if (node->left != NULL && node->right == NULL) {
            if (strcmp(parent->key, node->key) < 0) {
                parent->left = node->left;
            }else{
                parent->right = node->left;
            }
        }else{
            AVL_Node* largest_parent;
            AVL_Node* largest = node->left;
            while (largest->right != NULL) {
                largest = largest->right;
            }
            largest_parent = AVL_find_parent(tree, largest);
            largest_parent->right = NULL;
            free(node->key);
            node->key = largest->key;
            free(largest);
        }
    }else{
        if (comparison < 0 && node->left != NULL) {
            AVL_remove_node(tree, node->left, key);
        }else if (comparison > 0 && node->right != NULL) {
            AVL_remove_node(tree, node->right, key);
        }
    }

    AVL_rebalance(node);
}

AVL_Node* AVL_find_parent(AVL_Tree* tree, AVL_Node* child) {
    AVL_Node* parent = NULL;
    AVL_Node* node = tree->root;
    while (node != NULL) {
        if (strcmp(node->key, child->key) == 0) {
            return parent;
        }

        if (strcmp(node->key, child->key) < 0) {
            parent = node;
            node = node->left;
        }else{
            parent = node;
            node = node->right;
        }
    }
    return NULL;
}

void AVL_cleanup(AVL_Tree* tree)
{
    if (tree->root != NULL) {
        AVL_cleanup_node(tree->root);
    }
    free(tree);
}

void AVL_cleanup_node(AVL_Node* node)
{
    if (node != NULL) {
        AVL_cleanup_node(node->left);
        AVL_cleanup_node(node->right);
        free(node->key);
        free(node);
    }
}

int AVL_size(AVL_Node* node, int size) {
    if (node != NULL) {
        size = AVL_size(node->left, size);
        size = AVL_size(node->right, size);
        size++;
    }
    return size;
}
