#ifndef AVL_TREE
#define AVL_TREE

/*
 * Struct for a node of an AVL Tree.
 */
typedef struct AVL_Node {
    char* key;
    int count;
    int height;

    struct AVL_Node* left;
    struct AVL_Node* right;
} AVL_Node;

/*
 * Struct definition for an AVL Tree.
 */
typedef struct AVL_Tree {
    AVL_Node* root;
} AVL_Tree;

/*
 * Return the maximum of two integers.
 */
int max(int a, int b);

/*
 * Create a tree node and initializes default values. Both the node
 * and the key will need to be freed.
 */
AVL_Node* AVL_Node_create(char* key);

/*
 * Create an AVL tree. Root node is initialized as NULL.
 */
AVL_Tree* AVL_Tree_create();

/*
 * Search a tree for a given node. Found node will be returned, or
 * NULL in the case that no matching node was found.
 */
AVL_Node* AVL_search(AVL_Tree* tree, char* key);

/*
 * Left rotation.
 */
AVL_Node* AVL_rotate_left(AVL_Node* node);

/*
 * Right rotation.
 */
AVL_Node* AVL_rotate_right(AVL_Node* node);

/*
 * Left/right rotation.
 */
AVL_Node* AVL_rotate_left_right(AVL_Node* node);

/*
 * Right/left rotation.
 */
AVL_Node* AVL_rotate_right_left(AVL_Node* node);

/*
 * Rebalance a tree from a given node.
 */
AVL_Node* AVL_rebalance(AVL_Node* root);

/*
 * Insert a key in to a given tree.
 */
void AVL_insert(AVL_Tree* tree, char* key);

/*
 * Recursive function for inserting a node.
 */
AVL_Node* AVL_insert_node(AVL_Node* root, AVL_Node* node);

/*
 * Get the height of a node. Returns -1 if node is NULL.
 */
int AVL_node_height(AVL_Node* node);

/*
 * Remove the node with a given key from a tree. 
 */
void AVL_remove(AVL_Tree* tree, char* key);

/*
 * Remove a node from a tree. Used by AVL_remove.
 */
void AVL_remove_node(AVL_Tree* tree, AVL_Node* node, char* key);

/*
 * Find the parent of a given node. Will return NULL if the node was not
 * found or if the node is root.
 */
AVL_Node* AVL_find_parent(AVL_Tree* tree, AVL_Node* child);

/*
 * Cleanup a tree. Frees all memory associated with a tree.
 */
void AVL_cleanup(AVL_Tree* tree);

/*
 * Free all memory associated with a node. Child nodes will be
 * freed recursively.
 */
void AVL_cleanup_node(AVL_Node* node);

/*
 * Calculate the size of a tree from a given node.
 */
int AVL_size(AVL_Node* node, int size);

#endif
