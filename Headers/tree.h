#ifndef TREE_H
#define TREE_H

#include "task.h"

/**
 * @brief Enum for sorting keys used in the binary search tree.
 */
typedef enum {
    KEY_ID,       // Sort by task ID
    KEY_PRIORITY, // Sort by task priority
    KEY_STATUS    // Sort by task status
} SortKey;

/**
 * @brief Structure for a binary search tree node.
 */
typedef struct TreeNode {
    Task *task;               // Pointer to a Task
    struct TreeNode *left;    // Left child
    struct TreeNode *right;   // Right child
} TreeNode;

/**
 * @brief Structure for the binary search tree.
 */
typedef struct Tree {
    TreeNode *root;           // Root of the BST
    SortKey key;              // Key to sort by (ID, priority, status)
} Tree;

/**
 * @brief Creates a new binary search tree with a specified sort key.
 *
 * @param key The key to sort by (ID, priority, or status).
 * @return Pointer to the new Tree, or NULL if allocation fails.
 */
Tree* tree_create(SortKey key);

/**
 * @brief Inserts a task into the binary search tree.
 *
 * Places the task in the correct position based on the tree's sort key.
 *
 * @param tree Pointer to the tree.
 * @param task Pointer to the Task to insert.
 */
void tree_insert(Tree *tree, Task *task);

/**
 * @brief Prints all tasks in the tree in sorted order (inorder traversal).
 *
 * Displays tasks sorted by the tree's sort key.
 *
 * @param tree Pointer to the tree.
 */
void tree_printInorder(Tree *tree);

/**
 * @brief Frees all nodes in the tree (but not the tasks).
 *
 * Tasks are not freed as they are owned by the linked list.
 *
 * @param tree Pointer to the tree.
 */
void tree_free(Tree *tree);

#endif
