#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

/**
 * @brief Creates a new binary search tree with a specified sort key.
 *
 * @param key The key to sort by (ID, priority, or status).
 * @return Pointer to the new Tree, or NULL if allocation fails.
 */
Tree* tree_create(SortKey key) {
    Tree *tree = malloc(sizeof(Tree));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->key = key;
    return tree;
}

/**
 * @brief Compares two tasks based on the specified sort key.
 *
 * @param t1 First task to compare.
 * @param t2 Second task to compare.
 * @param key The sort key (ID, priority, or status).
 * @return Negative if t1 < t2, positive if t1 > t2, zero if equal.
 */
static int compareTasks(Task *t1, Task *t2, SortKey key) {
    switch (key) {
        case KEY_ID: return t1->id - t2->id;
        case KEY_PRIORITY: return t1->priority - t2->priority;
        case KEY_STATUS: return t1->status - t2->status;
        default: return 0;
    }
}

/**
 * @brief Inserts a task into a subtree recursively.
 *
 * @param node Pointer to the current node (or NULL for new node).
 * @param task Pointer to the Task to insert.
 * @param key The sort key.
 */
static void tree_insertNode(TreeNode **node, Task *task, SortKey key) {
    if (!*node) {
        *node = malloc(sizeof(TreeNode));
        if (!*node) return;
        (*node)->task = task;
        (*node)->left = (*node)->right = NULL;
        return;
    }

    int cmp = compareTasks(task, (*node)->task, key);
    if (cmp < 0)
        tree_insertNode(&(*node)->left, task, key);
    else
        tree_insertNode(&(*node)->right, task, key);
}

/**
 * @brief Inserts a task into the binary search tree.
 *
 * Places the task in the correct position based on the tree's sort key.
 *
 * @param tree Pointer to the tree.
 * @param task Pointer to the Task to insert.
 */
void tree_insert(Tree *tree, Task *task) {
    if (!tree || !task) return;
    tree_insertNode(&tree->root, task, tree->key);
}

/**
 * @brief Prints tasks in a subtree using inorder traversal.
 *
 * @param node Pointer to the current node.
 */
static void tree_printInorderNode(TreeNode *node) {
    if (!node) return;
    tree_printInorderNode(node->left);
    printTask(node->task);
    tree_printInorderNode(node->right);
}

/**
 * @brief Prints all tasks in the tree in sorted order (inorder traversal).
 *
 * Displays tasks sorted by the tree's sort key.
 *
 * @param tree Pointer to the tree.
 */
void tree_printInorder(Tree *tree) {
    if (!tree || !tree->root) {
        printf("No tasks to display.\n");
        return;
    }
    printf("\n> Tasks Sorted by ");
    switch (tree->key) {
        case KEY_ID: printf("ID:\n"); break;
        case KEY_PRIORITY: printf("Priority:\n"); break;
        case KEY_STATUS: printf("Status:\n"); break;
    }
    printf("---------------------------------\n");
    tree_printInorderNode(tree->root);
}

/**
 * @brief Frees a subtree recursively (but not the tasks).
 *
 * @param node Pointer to the current node.
 */
static void tree_freeNode(TreeNode *node) {
    if (!node) return;
    tree_freeNode(node->left);
    tree_freeNode(node->right);
    free(node);
}

/**
 * @brief Frees all nodes in the tree (but not the tasks).
 *
 * Tasks are not freed as they are owned by the linked list.
 *
 * @param tree Pointer to the tree.
 */
void tree_free(Tree *tree) {
    if (!tree) return;
    tree_freeNode(tree->root);
    free(tree);
}
