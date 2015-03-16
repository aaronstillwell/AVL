
/*
 * Option 1 at the prompt. Requests the name of
 * a file, then loads the information from that file in to the AVL tree.
 */
void load();

/*
 * Option 2 at the prompt. Search the AVL tree
 * for a given key.
 */
void search();

/*
 * Option 3 at the prompt. Insert a new key in to the tree. If the key
 * already exists, then its count is incremented.
 */
void insert();

/*
 * Option 4 at the prompt. Remove a given node from the AVL tree.
 */
void remove_node();

/*
 * Option 5 at the prompt. Print the height and size of the current tree.
 */
void size();

/*
 * Display all nodes within a frequency above a given number. Uses inorder
 * traversal.
 */
void above_frequency(AVL_Node* node, int freq);

/*
 * Option 6 at the prompt. Makes use of above_frequency to display all nodes
 * in the tree that have a frequency greater than some arbitrary value
 * provided by the user.
 */
void display_all();
