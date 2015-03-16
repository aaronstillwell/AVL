#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "AVL_Tree.h"
#include "util.h"

/* The AVL tree struct we'll use */
AVL_Tree* tree;

void load() {
    char buffer[1001];
    FILE* file;
    printf("Filename: ");
    fgets(buffer, 1000, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    file = fopen(buffer, "r");
    if (!file) {
        puts("Error: No such file!");
    }else{
        char line[1000];
        while (fgets(line, 1000, file)) {
            char* token = strtok(line, " ");
            while (token != NULL) {
                if (!is_string_empty(token)) {
                    AVL_Node* node;
                    if (token[strlen(token) - 1] == '\n') {
                        token[strlen(token) - 1] = '\0';
                    }
                    node = AVL_search(tree, token);
                    if (node == NULL) {
                        AVL_insert(tree, token);
                    }else{
                        node->count++;
                    }
                }
                token = strtok(NULL, " ");
            }
        }
        printf("File loaded\n");
        fclose(file);
    }
}

void search() {
    char buffer[1001];
    AVL_Node* search;

    printf("Find key: ");
    fgets(buffer, 1000, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    search = AVL_search(tree, buffer);

    if (search != NULL) {
        printf("key: %s, frequency: %d\n", search->key, search->count);
    }else{
        puts("no_such_key");
    }
}

void insert() {
    char buffer[1001];
    AVL_Node* search;

    printf("Insert key: ");
    fgets(buffer, 1000, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    search = AVL_search(tree, buffer);
    if (search == NULL) {
        AVL_insert(tree, buffer);
        printf("key: %s, frequency: %d\n", buffer, 1);
    }else{
        search->count++;
        printf("key: %s, frequency: %d\n", search->key, search->count);
    }
}

void remove_node() {
    char buffer[1001];
    AVL_Node* search;

    printf("Remove key: ");
    fgets(buffer, 1000, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    search = AVL_search(tree, buffer);
    if (search == NULL) {
        printf("no_such_key\n");
    }else{
        if (search->count == 1) {
            printf("Node deleted\n");
            AVL_remove(tree, search->key);
        }else{
            search->count--;
            printf("Key: %s, frequency: %d\n", search->key, search->count);
        }
    }
}

void size() {
    int height = tree->root->height;
    int size = AVL_size(tree->root, 0);

    printf("Height: %d, Size: %d\n", height, size);
}

void above_frequency(AVL_Node* node, int freq) {
    if (node != NULL) {
        above_frequency(node->right, freq);
        if (node->count > freq) {
            printf("Key: %s, Frequency: %d\n", node->key, node->count);
        }
        above_frequency(node->left, freq);
    }
}

void display_all() {
    char buffer[1001];
    printf("Frequency: ");
    fgets(buffer, 1000, stdin);
    buffer[strlen(buffer) - 1] = '\0';

    above_frequency(tree->root, atoi(buffer));
}

int main(int argc, char* argv[])
{
    char input[4];
    tree = AVL_Tree_create();

    printf("----------------------------\n");
    printf("Menu:\n");
    printf("1. Initialization\n");
    printf("2. Find\n");
    printf("3. Insert\n");
    printf("4. Remove\n");
    printf("5. Check height and size\n");
    printf("6. Find all\n");
    printf("7. Exit\n");
    printf("----------------------------\n");

    while (input[0] != '7') {
        printf("avl/> ");
        fgets(input, 3, stdin);
        if (input[0] == '1') {
            load();
        }else if (input[0] == '2') {
            search();
        }else if (input[0] == '3') {
            insert();
        }else if (input[0] == '4') {
            remove_node();
        }else if (input[0] == '5') {
            size();
        }else if (input[0] == '6') {
            display_all();
        }else if (input[0] == '7') {
            printf("Exiting. Goodbye.\n");
        }
    }

    /* Free memory */
    AVL_cleanup(tree);

    return 0;
}
